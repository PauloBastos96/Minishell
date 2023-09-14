/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:04:18 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/14 13:22:26 by paulorod         ###   ########.fr       */
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
		if (cmd->cmd)
		{
			while (cmd->cmd[i])
			{
				free(cmd->cmd[i]);
				cmd->cmd[i] = NULL;
				i++;
			}
			free(cmd->cmd);
			cmd->cmd = NULL;
		}
		if (cmd->path)
			free(cmd->path);
		free_redirs(cmd->redirs);
		temp = cmd->next;
		if (cmd)
			free(cmd);
		cmd = temp;
	}
}

/*Free commands, envs and shell variables*/
void	free_all(t_shell *shell)
{
	free_cmd(shell->cmd);
	free_envs(shell);
	free(shell);
}
