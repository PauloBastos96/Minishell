/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:46:47 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/18 22:19:23 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Copies 'n' bytes from 'src' to 'dest'
Returns pointer to 'dest'*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*tmp_src;
	char	*tmp_dest;

	if (!src && !dest)
		return (NULL);
	tmp_src = (char *)src;
	tmp_dest = dest;
	while (n--)
		*tmp_dest++ = *tmp_src++;
	return (dest);
}
