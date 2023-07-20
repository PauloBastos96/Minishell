/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:46:25 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/20 20:06:14 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Sets 'n' bytes of memory starting at the location pointed by '*s' to 'c'*/
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)s;
	while (n--)
		*tmp++ = c;
	return (s);
}
