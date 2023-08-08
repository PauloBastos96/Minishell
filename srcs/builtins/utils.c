/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:38:12 by vpacheco          #+#    #+#             */
/*   Updated: 2023/08/08 14:01:28 by paulorod         ###   ########.fr       */
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
