/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:16:56 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/24 15:24:23 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../minishell.h"

/*Search for command executable in PATH directories
	and return the full path*/
static char	*get_full_path(char **paths, char *command)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], command);
		if (!access(full_path, F_OK))
		{
			free(command);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

void	clear_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

/*Get command executable path*/
char	*search_command_path(char *command)
{
	char	*path_var;
	char	**paths;
	char	*full_path;
	char	*cmd_path;

	path_var = getenv("PATH");
	if (path_var)
		paths = ft_split(path_var, ':');
	else
		return (NULL);
	if (paths)
	{
		cmd_path = ft_strjoin("/", command);
		full_path = get_full_path(paths, cmd_path);
		if (!full_path)
			print_fd("Command not found", 2, command);
		clear_paths(paths);
		return (full_path);
	}
	return (NULL);
}

/*Create sub-process for command*/
int	create_command_process(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		status;

	g_using_sub_process = true;
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd->path, cmd->cmd, (char **)env) == -1)
			perror(NULL);
		exit(0);
	}
	else
	{
		wait(&status);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_using_sub_process = false;
	}
	return (status);
}

/*Replace environment variables with their value*/
char	*handle_env_vars(char *command, char ***env)
{
	char	*env_var;
	char	*env_value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (command[i])
	{
		if (command[i] == '$')
		{
			j = i + 1;
			while (command[i] && command[i] != ' ')
				i++;
			env_var = ft_substr(command, j, i - j);
			env_value = ft_getenv(env_var, env);
			free(command);
			free(env_var);
			if (env_value)
				return (ft_strdup(env_value));
			return (NULL);
		}
		i++;
	}
	return (command);
}

/*Create command struct*/
char	**create_cmd(char *command, char ***env)
{
	char			**cmd;
	int				pos;
	size_t			i;
	unsigned int	j;

	cmd = alloc_cmd(command);
	i = 0;
	j = 0;
	pos = 0;
	while (command[i])
	{
		if (command[i] == ' ')
		{
			cmd[pos] = handle_env_vars(ft_substr(command, j, i - j), env);
			pos++;
			j = i + 1;
		}
		else if (!command[i + 1])
		{
			cmd[pos] = handle_env_vars(ft_substr(command, j, i + 1 - j), env);
			j = i + 1;
		}
		i++;
	}
	return (cmd);
}
