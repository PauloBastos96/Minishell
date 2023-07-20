/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:22:41 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/18 22:19:27 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Moves 'n' bytes from 'src' to 'dest'
Returns pointer to 'dest'*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*tmp_src;
	char	*tmp_dest;

	if (!src && !dest)
		return (NULL);
	tmp_src = (char *)src;
	tmp_dest = (char *)dest;
	if (tmp_src < tmp_dest)
	{
		while (n--)
			*(tmp_dest + n) = *(tmp_src + n);
		return (dest);
	}
	while (n--)
		*tmp_dest++ = *tmp_src++;
	return (dest);
}
