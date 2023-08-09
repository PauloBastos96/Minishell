/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:38:13 by paulorod          #+#    #+#             */
/*   Updated: 2023/07/28 15:39:05 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Compare two strings
//Return 0 if equal, positive if s1 > s2, negative if s1 < s2
int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*c1;
	unsigned char	*c2;
	unsigned int	i;

	i = 0;
	c1 = (unsigned char *) s1;
	c2 = (unsigned char *) s2;
	while (c1[i])
	{
		if (c1[i] == c2[i])
			i++;
		else
			return (c1[i] - c2[i]);
	}
	return (c1[i] - c2[i]);
}
