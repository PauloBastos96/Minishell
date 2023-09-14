/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 09:56:07 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/14 12:44:34 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Close file descriptor*/
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

/*Swap file descriptor*/
void	swap_fd(int *fd, int target)
{
	close_safe(fd);
	*fd = target;
}

void	bind_std(t_shell *shell)
{
	t_redirs	*redirs;
	t_cmd		*cmd;

	cmd = shell->cmd;
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
		if (cmd->redirs->indentifier == less)
			handle_redir_in(shell);
		else if (cmd->redirs->indentifier == great)
			handle_redir_out(shell);
		else if (cmd->redirs->indentifier == append)
			handle_redir_out_append(shell);
		else if (cmd->redirs->indentifier == h_doc)
			handle_redir_hdoc(shell);
		cmd->redirs = cmd->redirs->next;
	}
	cmd->redirs = redirs;
}

/*Execute pipe process*/
void	pipe_process(t_shell *shell)
{
	t_cmd	*cmd;
	int		status;

	cmd = shell->cmd;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	bind_std(shell);
	cmd->dup_fd[0] = dup2(cmd->std.in, STDIN_FILENO);
	cmd->dup_fd[1] = dup2(cmd->std.out, STDOUT_FILENO);
	if (cmd->dup_fd[0] == -1 || cmd->dup_fd[1] == -1)
	{
		close_safe(&cmd->std.out);
		close_safe(&cmd->std.in);
		close_safe(&cmd->dup_fd[0]);
		close_safe(&cmd->dup_fd[1]);
		perror("dups");
		free_all(shell);
		exit(1);
	}
	close_safe(&cmd->std.out);
	close_safe(&cmd->std.in);
	handle_commands(shell);
	close_safe(&cmd->dup_fd[0]);
	close_safe(&cmd->dup_fd[1]);
	status = shell->status;
	free_all(shell);
	exit(status);
}

/*Execute pipes*/
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
		pipe_process(shell);
	return (0);
}
