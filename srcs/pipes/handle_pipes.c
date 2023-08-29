/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 09:56:07 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/08/29 16:16:27 by ffilipe-         ###   ########.fr       */
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
	if (pipe((*cmd_struct)->fd) == -1)
		return (1);
	(*cmd_struct)->pid = fork();
	if ((*cmd_struct)->pid == 0)
	{
		dup2((*cmd_struct)->fd[1], STDOUT_FILENO);
		close((*cmd_struct)->fd[0]);
		close((*cmd_struct)->fd[1]);
		run_command((*cmd_struct), env);
	}
	(*cmd_struct)->next->pid = fork();
	if ((*cmd_struct)->next->pid == 0)
	{
		dup2((*cmd_struct)->next->fd[0], STDIN_FILENO);
		close((*cmd_struct)->next->fd[0]);
		close((*cmd_struct)->next->fd[1]);
		run_command((*cmd_struct)->next, env);
	}
	waitpid((*cmd_struct)->pid, NULL, 0);
	waitpid((*cmd_struct)->next->pid, NULL, 0);
	return (1);
}
