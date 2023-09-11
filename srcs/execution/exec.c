/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:45:36 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/11 14:07:11 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_builtin(t_cmd *cmd)
{
	if (!cmd->cmd[0])
		return (false);
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (true);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (true);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (true);
	return (false);
}

void	start_exec(t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*start;

	start = shell->cmd;
	if (!shell->cmd->next && is_builtin(shell->cmd))
	{
		handle_commands(shell);
		return ;
	}
	while (shell->cmd)
	{
		cmd = shell->cmd;
		exec_pipes(shell);
		if (cmd->prev)
			close_safe(&cmd->prev->fd[0]);
		close_safe(&cmd->fd[1]);
		if (!cmd->next)
			close_safe(&cmd->fd[0]);
		shell->cmd = shell->cmd->next;
	}
	shell->cmd = start;
	while (shell->cmd)
	{
		waitpid(shell->cmd->pid, &shell->status, 0);
		if (WIFEXITED(shell->cmd->status))
			shell->status = WEXITSTATUS(shell->status);
		shell->cmd = shell->cmd->next;
	}
}

// Main shell loop
//! readline has memory leaks that don't have to be fixed
void	shell_loop(t_shell *shell)
{
	char	*command;

	while (true)
	{
		command = readline(PROMPT);
		if (!command)
		{
			printf("exit\n");
			exit(0);
		}
		if (*command)
		{
			add_history(command);
			if (ft_strlen(command) > 0)
			{
				shell->cmd = command_parser(command, shell);
				// exec_pipes(shell);
				start_exec(shell);
			}
			// handle_commands(shell);
			free_cmd(shell->cmd);
			//free(command); //!Double free here when using unclosed quotes
		}
	}
}
