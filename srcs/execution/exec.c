/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:45:36 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/25 17:09:25 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Create sub-process for command*/
int	create_command_process(t_cmd *cmd, char **env)
{
	if (execve(cmd->path, cmd->cmd, env) == -1)
		perror("execve");
	return (127);
}

/*Wait for sub process to complete*/
void	ft_wait(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		waitpid(cmd->pid, &cmd->status, 0);
		if (WIFEXITED(cmd->status))
			cmd->status = WEXITSTATUS(cmd->status);
		shell->status = cmd->status;
		cmd = cmd->next;
	}
}

/*Start command execution*/
void	start_exec(t_shell *shell)
{
	t_cmd	*cmd;

	shell->start = shell->cmd;
	if (!shell->cmd->next && is_builtin(shell->cmd) && !shell->cmd->redirs)
	{
		handle_commands(shell);
		return ;
	}
	g_using_sub_process = true;
	while (shell->cmd)
	{
		cmd = shell->cmd;
		cmd = set_quotes(cmd);
		exec_pipes(shell);
		if (cmd->prev)
			close_safe(&cmd->prev->fd[0]);
		close_safe(&cmd->fd[1]);
		if (!cmd->next)
			close_safe(&cmd->fd[0]);
		shell->cmd = shell->cmd->next;
	}
	shell->cmd = shell->start;
	ft_wait(shell);
	g_using_sub_process = false;
}

/*Exit shell with ctrl+d*/
void	exit_shell(t_shell *shell, char *cmd)
{
	free(cmd);
	printf("exit\n");
	free_envs(shell);
	exit(0);
}

// Main shell loop
//! readline has memory leaks that don't have to be fixed
void	shell_loop(t_shell *shell)
{
	char	*command;
	char	*trimmed;

	while (true)
	{
		command = readline(PROMPT);
		trimmed = NULL;
		if (command)
			trimmed = ft_strtrim(command, "\n\r\t \v");
		if (!trimmed)
			exit_shell(shell, command);
		trimmed = pre_extend_env_vars(trimmed, shell, false);
		if (ft_strlen(trimmed) > 0)
		{
			(add_history(command), free(command));
			shell->cmd = command_parser(trimmed, shell);
			if (shell->cmd)
			{
				start_exec(shell);
				free_cmd(shell);
				continue ;
			}
		}
		(free(trimmed), free(command));
	}
}
