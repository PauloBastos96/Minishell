/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 09:56:07 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/01 15:14:46 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_pipes(t_shell *shell)
{
	if (pipe(shell->cmd->fd) == -1)
		return (1);
	shell->cmd->pid = fork();
	if (shell->cmd->fd[0] == 0)
	{
		dup2(shell->cmd->fd[0], STDOUT_FILENO);
		close(shell->cmd->fd[1]);
		close(shell->cmd->fd[0]);
		run_command(shell);
	}
	shell->cmd = shell->cmd->next;
	run_command(shell);
	return (1);
}
