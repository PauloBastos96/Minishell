/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 09:56:07 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/06 16:06:36 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	close_safe(int *fd)
{
	int	result;

	if (*fd == -1)
		return (0);
	result = close(*fd);
	if (result == 0)
		*fd = -1;
	return (result);
}

int	exec_pipes(t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*start;

	start = shell->cmd;
	while (shell->cmd)
	{
		cmd = shell->cmd;
		if (pipe(cmd->fd) == -1)
		{
			// TODO: PROPER ERROR HANDLING
			perror("pipe");
			return (1);
		}
		//!FOUND THE ISSUE, FDs FROM PREV ARE SET TO -1, MOST LIKELY BECAUSE THIS IS BEING SET IN A SUB PROCESS
		if (cmd->prev)
			cmd->dup_fd[0] = dup2(cmd->prev->fd[0], STDIN_FILENO);
		else
			cmd->dup_fd[0] = dup(STDIN_FILENO);
		if (cmd->next)
			cmd->dup_fd[1] = dup2(cmd->fd[1], STDOUT_FILENO);
		else
			cmd->dup_fd[1] = dup(STDOUT_FILENO);
		if (cmd->dup_fd[0] == -1 || cmd->dup_fd[1] == -1)
		{
			close_safe(&cmd->fd[1]);
			close_safe(&cmd->fd[0]);
			close_safe(&cmd->dup_fd[0]);
			close_safe(&cmd->dup_fd[1]);
			perror("dups");
			exit (1);
		}
		handle_commands(shell);
		shell->cmd = shell->cmd->next;
	}
	shell->cmd = start;
	while (shell->cmd)
	{
		if (cmd->prev)
			close_safe(&cmd->prev->fd[0]);
		close_safe(&cmd->fd[1]);
		close_safe(&cmd->fd[0]);
		close_safe(&cmd->dup_fd[0]);
		close_safe(&cmd->dup_fd[1]);
		shell->cmd = shell->cmd->next;
	}
	return (0);
}
