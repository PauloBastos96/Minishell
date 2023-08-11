/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:49:20 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/11 15:01:47 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/list.h"
#include "../../includes/builtins.h"
#include "../../minishell.h"

/*Builtin exit command*/
int	ft_exit(t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->cmd[1])
	{
		if (is_exit_code_valid(cmd->cmd[1]))
			exit_code = ft_atoi(cmd->cmd[1]);
		else
		{
			printf("exit: %s: numeric argument required\n", cmd->cmd[1]);
			return (1);
		}
	}
	free(cmd->cmd);
	rl_clear_history();
	exit(exit_code);
}

/*Builtin export command*/
int	ft_export(t_cmd *cmd, const char **env)
{
	int		i;
	char	**sorted;

	i = 0;
	while (env[i])
		i++;
	sorted = ft_calloc(sizeof(char *), i);
	if (!cmd->cmd[1])
	{
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
				printf("%s\n", sorted[i]);
			i++;
		}
	}
	return (0);
}
