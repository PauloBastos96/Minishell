/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:58:40 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/18 14:38:07 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Compares first 'n' bytes from 's1' and 's2'
Returns 0 if the values are the same and 1 or -1 depending on the difference*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;

	i = 0;
	c1 = (unsigned char *) s1;
	c2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (i < n - 1)
	{
		if (c1[i] == c2[i])
			i++;
		else
			break ;
	}
	return (c1[i] - c2[i]);
}
