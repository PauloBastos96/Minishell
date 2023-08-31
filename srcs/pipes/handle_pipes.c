/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 09:56:07 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/08/30 13:29:02 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_pipe_cmds(t_cmd **cmd, char *command, char **env)
{
	t_cmd	*tmp;
	char	**cmd_args;
	int		i;

	i = 0;
	tmp = *cmd;
	if (check_valid_pipe(command) == 1)
	{
		cmd_args = ft_split(command, '|');
		while (cmd_args[i])
		{
			command_parser(cmd, cmd_args[i]);
			i++;
		}
	}
	else
		print_fd("No such file or directory", 2, command);
	start_exec(cmd, env);
	return ;
}

int	start_exec(t_cmd **cmd_struct, char **env)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		run_command((*cmd_struct), env);
	}
	(*cmd_struct) = (*cmd_struct)->next;
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		run_command((*cmd_struct), env);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
