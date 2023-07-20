/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:41:16 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/24 20:53:25 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Get size of the created substring to allocate*/
static int	get_alloc_size(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
			j++;
		i++;
	}
	return (j + 1);
}

/*Allocates and returns a substring from the string ’s’.
The substring begins at index ’start’ and is of maximum size ’len’.*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*sub;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	sub = malloc(get_alloc_size(s, start, len) * sizeof(char));
	if (!sub)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			sub[j] = s[i];
			j++;
		}
		i++;
	}
	sub[j] = '\0';
	return (sub);
}
