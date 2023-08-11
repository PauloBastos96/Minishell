/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:49:20 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/11 16:04:52 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/list.h"
#include "../../includes/builtins.h"
#include "../../minishell.h"

/*Export command with no arguments*/
int	export_noarg(char **sorted, const char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		sorted[i] = ft_strdup(env[i]);
		i++;
	}
	i = 0;
	sorted = sort_envs(sorted);
	while (sorted[i])
	{
		if (ft_isalpha(*sorted[i]))
			printf("declare -x %s\n", sorted[i]);
		i++;
	}
	return (0);
}

/*Builtin export command*/
int	ft_export(t_cmd *cmd, const char **env)
{
	int		i;
	char	**sorted;

	i = 0;
	while (env[i])
		i++;
	sorted = ft_calloc(sizeof(char *), i + 1);
	if (!cmd->cmd[1])
		return (export_noarg(sorted, env));
	return (0);
}
