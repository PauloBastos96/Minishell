/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:52:56 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/08 16:09:47 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function is not in use for now*/
void	ft_env_not_in_use(t_list **env_list)
{
	t_list	*env;

	env = *env_list;
	while (env)
	{
		printf("%s\n", (char *)env->content);
		env = env->next;
	}
}
