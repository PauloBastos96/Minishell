/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:32:52 by paulorod          #+#    #+#             */
/*   Updated: 2023/07/20 16:09:20 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Compare n bytes of two strings
//Return 0 if equal, positive if s1 > s2, negative if s1 < s2
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	unsigned int	i;

	i = 0;
	c1 = (unsigned char *) s1;
	c2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (c1[i])
	{
		if (c1[i] == c2[i] && i < n - 1)
			i++;
		else
			return (c1[i] - c2[i]);
	}
	return (c1[i] - c2[i]);
}
