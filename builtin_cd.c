/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:49:13 by paulorod          #+#    #+#             */
/*   Updated: 2023/07/24 13:24:48 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns the home path when using '~'*/
static char	*get_home_path(char *path)
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

/*Builtin cd command*/
void	ft_cd(char *command)
{
	char	*path;
	bool	can_free;

	can_free = true;
	path = ft_strtrim(command, "cd ");
	if (ft_strncmp(path, "~", 1) == 0)
		path = get_home_path(path);
	if (chdir(path) == -1)
		perror(NULL);
	if (can_free)
		free(path);
}
