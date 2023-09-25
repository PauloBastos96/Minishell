/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:04:18 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/25 14:49:59 by paulorod         ###   ########.fr       */
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
void	free_cmd(t_shell *shell)
{
	int		i;
	t_cmd	*temp;

	while (shell->cmd)
	{
		i = 0;
		if (shell->cmd->cmd)
		{
			while (shell->cmd->cmd[i])
			{
				free(shell->cmd->cmd[i]);
				shell->cmd->cmd[i] = NULL;
				i++;
			}
			free(shell->cmd->cmd);
			shell->cmd->cmd = NULL;
		}
		if (shell->cmd->path)
			free(shell->cmd->path);
		free_redirs(shell->cmd->redirs);
		temp = shell->cmd->next;
		if (shell->cmd)
			free(shell->cmd);
		shell->cmd = temp;
	}
}

/*Free commands, envs and shell variables*/
void	free_all(t_shell *shell)
{
	free_cmd(shell);
	free_envs(shell);
}

/*Replace old value with new*/
char	*replace_string(char *old, char *new)
{
	if (old)
		free(old);
	old = ft_strdup(new);
	free(new);
	return (old);
}
