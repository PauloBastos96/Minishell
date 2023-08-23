/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:38:12 by vpacheco          #+#    #+#             */
/*   Updated: 2023/08/23 12:40:37 by paulorod         ###   ########.fr       */
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

/*Add quotes after = sign*/
char	*add_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(sizeof(char), ft_strlen(str) + 3);
	while (str[i])
	{
		if (str[i] == '=')
		{
			new[j++] = str[i++];
			new[j++] = '"';
			while (str[i])
				new[j++] = str[i++];
			new[j++] = '"';
			new[j] = '\0';
			free(str);
			return (new);
		}
		new[j++] = str[i++];
	}
	free(str);
	return (new);
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
