/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:45:36 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/20 15:57:04 by paulorod         ###   ########.fr       */
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

/*Check if command is a builtin*/
bool	is_builtin(t_cmd *cmd)
{
	cmd = set_quotes(cmd);
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

/*Start command execution*/
void	start_exec(t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*start;

	start = shell->cmd;
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
	shell->cmd = start;
	ft_wait(shell);
	g_using_sub_process = false;
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
		if (command)
			trimmed = ft_strtrim(command, "\n\r\t \v");
		else
			trimmed = NULL;
		free(command);
		if (!trimmed)
		{
			printf("exit\n");
			free_envs(shell);
			free(shell);
			exit(0);
		}
		if (ft_strlen(trimmed) > 0)
		{
			add_history(trimmed);
			shell->cmd = command_parser(trimmed, shell);
			if (!shell->cmd)
				continue ;
			start_exec(shell);
			free_cmd(shell);
		}
	}
}
