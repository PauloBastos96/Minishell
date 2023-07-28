/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviro_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:13:03 by paulorod          #+#    #+#             */
/*   Updated: 2023/07/28 14:44:35 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Create list with enviroment variables*/
t_list	**new_env_list(char **env)
{
	t_list	**env_list;
	int		i;

	i = 0;
	env_list = ft_calloc(sizeof(t_list), 1);
	while (env[i])
	{
		ft_lstadd_back(env_list, ft_lstnew(env[i]));
		i++;
	}
	ft_lstadd_back(env_list, NULL);
	return (env_list);
}

/*Clear the enviroment variables list*/
void	clear_env_list(t_list **env_list)
{
	t_list	*env;
	t_list	*tmp;

	env = *env_list;
	while (env)
	{
		tmp = env->next;
		free(env);
		env = tmp;
	}
}
