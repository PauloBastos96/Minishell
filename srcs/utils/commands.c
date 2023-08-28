/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:16:56 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/28 15:37:16 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/commands.h"
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
static char	*handle_envs(char *command, t_shell *shell)
{
	char	*env_value;

	env_value = parse_command(command, shell);
	if (env_value && *env_value)
	{
		free(command);
		return (env_value);
	}
	else if (env_value)
		free(env_value);
	return (command);
}

/*Create command struct*/
char	**create_cmd(char *_cmd, t_shell *shell)
{
	char			**cmd;
	int				pos;
	size_t			i;
	unsigned int	j;

	cmd = alloc_cmd(_cmd);
	i = 0;
	j = 0;
	pos = 0;
	while (_cmd[i])
	{
		if (_cmd[i] == ' ')
		{
			cmd[pos] = handle_envs(ft_substr(_cmd, j, i - j), shell);
			pos++;
			j = i + 1;
		}
		else if (!_cmd[i + 1])
		{
			cmd[pos] = handle_envs(ft_substr(_cmd, j, i + 1 - j), shell);
			j = i + 1;
		}
		i++;
	}
	return (cmd);
}
