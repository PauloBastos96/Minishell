/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:45:36 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/05 14:41:25 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void start_exec(t_shell *shell)
{
    t_cmd *cmd;
    t_cmd *start;

    start = shell->cmd;
    while(shell->cmd)
    {
        cmd = shell->cmd;
        if(cmd->indentifier == 0)
            exec_pipes(shell);
        if(cmd->indentifier == 1)
            handle_redir_out(cmd);
        shell->cmd = shell->cmd->next;
    }
    while (shell->cmd)
	{
		waitpid(shell->cmd->pid, &shell->cmd->status, 0);
		if (WIFEXITED(shell->cmd->status))
			shell->cmd->status = WEXITSTATUS(shell->cmd->status);
		shell->cmd = shell->cmd->next;
	}
}

//Main shell loop
//!readline has memory leaks that don't have to be fixed
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
				exec_pipes(shell);
                //start_exec(shell);
			}
			break ;
			//handle_commands(shell);
			//free_cmd(shell->cmd);
		}
	}
}