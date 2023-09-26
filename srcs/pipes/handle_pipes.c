/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 09:56:07 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/25 16:37:56 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Close duplicated file descriptors*/
void	close_dup(t_cmd *cmd)
{
	close_safe(&cmd->dup_fd[0]);
	close_safe(&cmd->dup_fd[1]);
}

/*Handle redirections*/
void	handle_redirs(t_cmd *cmd, t_shell *shell)
{
	t_redirs	*redirs;

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

/*Setup file descriptors*/
void	bind_std(t_shell *shell)
{
	t_cmd	*cmd;

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
	handle_redirs(cmd, shell);
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
		close_std(cmd);
		close_dup(cmd);
		perror("dups");
		free_all(shell);
		exit(1);
	}
	close_std(cmd);
	handle_commands(shell);
	close_dup(cmd);
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
		perror("pipe");
		return (1);
	}
	cmd->pid = fork();
	if (cmd->pid == 0)
		pipe_process(shell);
	return (0);
}
