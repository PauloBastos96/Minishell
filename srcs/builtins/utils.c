/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpacheco <vpacheco@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:38:12 by vpacheco          #+#    #+#             */
/*   Updated: 2023/08/02 17:48:07 by vpacheco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/list.h"

//função que fizeste
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