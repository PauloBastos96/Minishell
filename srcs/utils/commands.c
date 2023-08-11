/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:16:56 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/10 16:30:09 by paulorod         ###   ########.fr       */
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
			free(paths);
			free(command);
			return (full_path);
		}
		i++;
	}
	return (NULL);
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
	if (paths)
	{
		cmd_path = ft_strjoin("/", command);
		full_path = get_full_path(paths, cmd_path);
		if (!full_path)
			print_fd("Command not found", 2, command);
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
		if (execve(cmd->path, cmd->cmd, env) == -1)
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
	free(cmd->path);
	return (status);
}
