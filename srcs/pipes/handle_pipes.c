/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 09:56:07 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/07 15:54:34 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	close_safe(int *fd)
{
	int	result;

	if (*fd == -1)
		return (0);
	result = close(*fd);
	if (result == 0)
		*fd = -1;
	return (result);
}

void	swap_fd(int *fd, int target)
{
	close_safe(fd);
	*fd = target;
}

void	bind_std(t_cmd *cmd)
{
	t_redirs	*redirs;

	cmd->std.in = dup(STDIN_FILENO);
	cmd->std.out = dup(STDOUT_FILENO);
	if (cmd->prev)
		swap_fd(&cmd->std.in, cmd->prev->fd[0]);
	if (cmd->next)
		swap_fd(&cmd->std.out, cmd->fd[1]);
	else
		close_safe(&cmd->fd[1]);
	close_safe(&cmd->fd[0]);
	redirs = cmd->redirs;
	while (cmd->redirs)
	{
		if (cmd->redirs->indentifier == lesser)
			handle_redir_in(cmd);
		if (cmd->redirs->indentifier == greater)
			handle_redir_out(cmd);
		cmd->redirs = cmd->redirs->next;
	}
	cmd->redirs = redirs;
}

int	exec_pipes(t_shell *shell)
{
	t_cmd	*cmd;

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
		bind_std(cmd);
		cmd->dup_fd[0] = dup2(cmd->std.in, STDIN_FILENO);
		cmd->dup_fd[1] = dup2(cmd->std.out, STDOUT_FILENO);
		if (cmd->dup_fd[0] == -1 || cmd->dup_fd[1] == -1)
		{
			close_safe(&cmd->std.out);
			close_safe(&cmd->std.in);
			close_safe(&cmd->dup_fd[0]);
			close_safe(&cmd->dup_fd[1]);
			perror("dups");
			exit(1);
		}
		close_safe(&cmd->std.out);
		close_safe(&cmd->std.in);
		handle_commands(shell);
		close_safe(&cmd->dup_fd[0]);
		close_safe(&cmd->dup_fd[1]);
		exit(shell->status);
	}
	return (0);
}
