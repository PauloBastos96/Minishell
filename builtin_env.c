/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:52:56 by paulorod          #+#    #+#             */
/*   Updated: 2023/07/28 12:52:08 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_list **env_list)
{
	t_list	*env;

	env = *env_list;
	while (env)
	{
		printf("%s\n", (char *)env->content);
		env = env->next;
	}
}
