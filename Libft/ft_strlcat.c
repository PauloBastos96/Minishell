/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:58:02 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/17 15:33:25 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Concatenates string 'src' to 'dst' up to 'size' characters
Returns size of created string*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	src_size;
	unsigned int	dest_size;

	i = 0;
	src_size = ft_strlen(src);
	dest_size = ft_strlen(dst);
	if (size <= dest_size)
		return (size + src_size);
	while (src[i] && dest_size + 1 < size)
	{
		dst[dest_size] = src[i];
		dest_size++;
		i++;
	}
	dst[dest_size] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
