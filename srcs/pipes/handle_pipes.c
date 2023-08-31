/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 09:56:07 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/08/31 16:29:50 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	start_exec(t_shell *shell)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	printf("%s\n", shell->cmd->cmd[0]);
	printf("%s\n", shell->cmd->cmd[1]);
	printf("%s\n", shell->cmd->cmd[2]);
	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		shell->cmd->path = search_command_path(shell->cmd->cmd[0]);
	}
	pid2 = fork();
	shell->cmd = shell->cmd->next;
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		run_command(shell);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
