/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:16:56 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/25 13:12:04 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../minishell.h"

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
