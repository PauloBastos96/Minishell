/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:38:12 by vpacheco          #+#    #+#             */
/*   Updated: 2023/09/27 13:16:31 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/list.h"
#include "../../minishell.h"

//Get home home path
char	*get_home_path(char *path)
{
	char	*home_path;
	char	*tmp;

	home_path = getenv("HOME");
	if (home_path)
	{
		tmp = ft_strtrim(path, "~");
		free(path);
		path = ft_strjoin(home_path, tmp);
		free(tmp);
	}
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

/*Add quotes after = sign*/
char	*add_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(sizeof(char), ft_strlen(str) + 3);
	if (!new)
		return (NULL);
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
	return (free(str), new);
}

/*Check if export expression is valid*/
bool	is_expression_valid(char *cmd, bool silent)
{
	if (!ft_isalpha(*cmd))
	{
		if (!silent)
		{
			write(2, "minishell: export: `", 20);
			write(2, cmd, ft_strlen(cmd));
			write(2, "': not a valid identifier\n", 26);
		}
		return (false);
	}
	return (true);
}
