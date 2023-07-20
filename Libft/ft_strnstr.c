/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:18:01 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/18 15:46:09 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Search 'len' characters in string 'big' for substring 'little'*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (big[i] && i < len)
	{
		k = i;
		if (little[j] == big[k])
		{
			while (little[j] == big[k] && k < len)
			{
				j++;
				k++;
				if (!little[j])
					return ((char *)&big[i]);
			}
		}
		i++;
		j = 0;
	}
	return (NULL);
}
