/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:49:20 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/21 16:25:44 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/list.h"
#include "../../includes/builtins.h"
#include "../../minishell.h"

/*Copy env and sort it to new array*/
char	**copy_and_sort_env(char **env)
{
	int		i;
	char	**new;

	i = 0;
	while (env[i])
		i++;
	new = ft_calloc(sizeof(new), i + 1);
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new = sort_envs(new);
	return (new);
}

/*Export command with no arguments*/
int	export_noarg(char **env)
{
	int		i;
	char	**sorted;

	sorted = copy_and_sort_env(env);
	i = 0;
	while (sorted[i])
	{
		if (ft_isalpha(*sorted[i]))
		{
			sorted[i] = add_quotes(sorted[i]);
			printf("declare -x %s\n", sorted[i]);
		}
		free(sorted[i]);
		i++;
	}
	free(sorted);
	return (0);
}

/*Export command with arguments*/
char	**export_witharg(char **new, char **env, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	j = 1;
	while (cmd->cmd[j])
	{
		new[i] = ft_strdup(cmd->cmd[j]);
		j++;
		i++;
	}
	return (new);
}

/*Builtin export command*/
int	ft_export(t_cmd *cmd, char **env)
{
	int		i;
	int		j;
	char	**array;

	if (!cmd->cmd[1])
		return (export_noarg(env));
	i = 0;
	j = 0;
	while (env[i])
		i++;
	while (cmd->cmd[j])
		j++;
	array = ft_calloc(sizeof(array), i + j + 1);
	env = export_witharg(array, env, cmd);
	return (0);
}
