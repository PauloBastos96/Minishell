/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:04:18 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/25 15:57:59 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../minishell.h"

/*Free redirections list*/
void	free_redirs(t_redirs *redirs)
{
	t_redirs	*tmp;

	while (redirs)
	{
		free(redirs->redirection);
		tmp = redirs->next;
		free(redirs);
		redirs = tmp;
	}
}

/*Free environment variables*/
void	free_envs(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		free(shell->env[i]);
		i++;
	}
	free(shell->env);
}

/*Free command struct*/
void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*temp;

	while (cmd)
	{
		i = 0;
		while (cmd->cmd[i])
		{
			printf("cleaning up %s[%p]\n", cmd->cmd[i], cmd->cmd[i]);
			free(cmd->cmd[i]);
			cmd->cmd[i] = NULL;
			i++;
		}
		if (cmd->path)
			free(cmd->path);
		free_redirs(cmd->redirs);
		close_safe(&cmd->fd[0]);
		close_safe(&cmd->fd[1]);
		close_safe(&cmd->std.in);
		close_safe(&cmd->std.out);
		close_safe(&cmd->h_doc[0]);
		close_safe(&cmd->h_doc[1]);
		free(cmd->cmd);
		temp = cmd->next;
		free(cmd);
		cmd = temp;
	}
}

/*Free commands, envs and shell variables*/
void	free_all(t_shell *shell)
{
	free_cmd(shell->start);
	free_envs(shell);
}
