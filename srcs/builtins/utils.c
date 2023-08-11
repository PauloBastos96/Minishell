/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:38:12 by vpacheco          #+#    #+#             */
/*   Updated: 2023/08/11 14:55:47 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/list.h"

//Get home home path
char	*get_home_path(char *path)
{
	char	*home_path;
	char	*tmp;

	home_path = getenv("HOME");
	tmp = ft_strtrim(path, "~");
	free(path);
	path = ft_strjoin(home_path, tmp);
	free(tmp);
	return (path);
}

/*Check if the exit code argument is valid*/
bool	is_exit_code_valid(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (false);
		i++;
	}
	return (true);
}

/*Sort enviroment variables by alphabetical order*/
char	**sort_envs(char **envs)
{
	bool	sorted;
	char	*temp;
	int		i;

	while (!sorted)
	{
		i = 0;
		sorted = true;
		while (envs[i])
		{
			if (envs[i + 1])
			{
				if (ft_strcmp(envs[i], envs[i + 1]) > 0)
				{
					temp = envs[i];
					envs[i] = envs[i + 1];
					envs[i + 1] = temp;
					sorted = false;
				}
			}
			i++;
		}
	}
	return (envs);
}
