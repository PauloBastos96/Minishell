/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:56:57 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/15 13:40:12 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Sort enviroment variables by alphabetical order*/
char	**sort_envs(char **envs)
{
	bool	is_sorted;
	char	*temp;
	int		i;

	is_sorted = false;
	while (!is_sorted)
	{
		i = 0;
		is_sorted = true;
		while (envs[i])
		{
			if (envs[i + 1])
			{
				if (ft_strcmp(envs[i], envs[i + 1]) > 0)
				{
					temp = envs[i];
					envs[i] = envs[i + 1];
					envs[i + 1] = temp;
					is_sorted = false;
				}
			}
			i++;
		}
	}
	return (envs);
}

/*Check if enviroment already contains inputed variable*/
bool	is_duplicate(char **env, char *new)
{
	int	i;
	int	length;

	i = 0;
	while (env[i])
	{
		length = 0;
		while (new[length] && new[length] != '=')
			length++;
		if (!ft_strncmp(env[i], new, length))
			return (true);
		i++;
	}
	return (false);
}
