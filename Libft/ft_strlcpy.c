/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:44:04 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/17 12:58:27 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Copies string 'src' to 'dst' up to 'size' characters
Returns size of copied string, or of 'src' if 'dst' can't fit it*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_size;
	size_t	dst_size;

	i = 0;
	src_size = ft_strlen(src);
	dst_size = ft_strlen(dst);
	if (size != 0)
	{
		while (src[i] && size - 1 > 0)
		{
			dst[i] = src[i];
			size--;
			dst_size--;
			i++;
		}
		dst[i] = '\0';
	}
	return (src_size);
}
