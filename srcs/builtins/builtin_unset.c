/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:55:18 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/28 13:03:40 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/list.h"
#include "../../includes/builtins.h"
#include "../../minishell.h"

/*Create new env array without removed env*/
char	**remove_env(char **env, int pos)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(sizeof(new_env), i);
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (i != pos)
		{
			new_env[j] = ft_strdup(env[i]);
			free(env[i]);
			j++;
		}
		else
			free(env[i]);
		i++;
	}
	return (new_env);
}

/*Remove env from envs*/
int	ft_unset(t_shell *shell)
{
	int		i;
	int		j;
	char	**new_env;

	i = 1;
	while (shell->cmd->cmd[i])
	{
		j = 0;
		while (shell->env[j])
		{
			if (!ft_strncmp(shell->cmd->cmd[i], shell->env[j],
					ft_strlen(shell->cmd->cmd[i])))
			{
				new_env = remove_env(shell->env, j);
				if (!new_env)
					return (1);
				free(shell->env);
				shell->env = new_env;
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
