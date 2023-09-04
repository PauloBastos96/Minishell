/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 09:56:07 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/04 15:06:20 by ffilipe-         ###   ########.fr       */
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
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
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
				return (1);
			}
			if (cmd->prev)
				close_safe(&cmd->prev->fd[0]);
			close_safe(&cmd->fd[1]);
			close_safe(&cmd->fd[0]);
			run_command(shell);
			close_safe(&cmd->dup_fd[0]);
			close_safe(&cmd->dup_fd[1]);
		}
		else
		{
			if (cmd->prev)
				close_safe(&cmd->prev->fd[0]);
			close_safe(&cmd->fd[1]);
			if (!cmd->next)
				close_safe(&cmd->fd[0]);
		}
		shell->cmd = shell->cmd->next;
	}
	shell->cmd = start;
	while (shell->cmd)
	{
		waitpid(shell->cmd->pid, &shell->cmd->status, 0);
		if (WIFEXITED(shell->cmd->status))
			shell->cmd->status = WEXITSTATUS(shell->cmd->status);
		shell->cmd = shell->cmd->next;
	}
	return (0);
}
