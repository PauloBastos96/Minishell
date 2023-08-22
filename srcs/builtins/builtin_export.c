/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:49:20 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/22 15:46:02 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/list.h"
#include "../../includes/builtins.h"
#include "../../minishell.h"

/*Copy env and sort it to new array*/
static char	**copy_and_sort_env(char **env)
{
	int		i;
	char	**new;

	i = 0;
	while (env[i])
		i++;
	new = ft_calloc(sizeof(new), i + 1);
	if (!new)
		return (NULL);
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
static int	export_noarg(char **env)
{
	int		i;
	char	**sorted;

	sorted = copy_and_sort_env(env);
	if (!sorted)
		return (1);
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

/*Add or update variable if it already exists*/
static char	*add_or_update_var(char *env, char **cmd)
{
	int	i;
	int	length;

	i = 1;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '='))
		{
			length = 0;
			while (cmd[i][length] != '=')
				length++;
			if (!ft_strncmp(env, cmd[i], length))
				return (ft_strdup(cmd[i]));
		}
		i++;
	}
	return (ft_strdup(env));
}

/*Export command with arguments*/
static char	**export_witharg(char **new, char **env, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		new[i] = add_or_update_var(env[i], cmd->cmd);
		i++;
	}
	j = 1;
	while (cmd->cmd[j])
	{
		if (!is_duplicate(env, cmd->cmd[j]))
			new[i] = ft_strdup(cmd->cmd[j]);
		j++;
		i++;
	}
	new[i] = 0;
	return (new);
}

/*Builtin export command*/
int	ft_export(t_cmd *cmd, char ***env)
{
	int		i;
	int		j;
	char	**array;
	char	**_env;

	if (!cmd->cmd[1])
		return (export_noarg(*env));
	i = 0;
	j = 0;
	_env = *env;
	while (_env[i])
		i++;
	while (cmd->cmd[j])
		j++;
	array = ft_calloc(sizeof(array), i + j);
	if (!array)
		return (1);
	array = export_witharg(array, *env, cmd);
	*env = array;
	return (0);
}
