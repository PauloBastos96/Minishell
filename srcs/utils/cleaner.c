/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:04:18 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/25 16:47:32 by ffilipe-         ###   ########.fr       */
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

	shell->cmd = shell->start;
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
		close_safe(&shell->cmd->fd[0]);
		close_safe(&shell->cmd->fd[1]);
		close_safe(&shell->cmd->std.in);
		close_safe(&shell->cmd->std.out);
		close_safe(&shell->cmd->h_doc[0]);
		close_safe(&shell->cmd->h_doc[1]);
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
