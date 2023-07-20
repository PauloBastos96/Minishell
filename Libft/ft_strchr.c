/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:51:22 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/19 20:25:33 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns a pointer to the first occurence of the provided character 'c'*/
char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)s;
	while (tmp[i])
	{
		if (tmp[i] == (char)c)
			return (&tmp[i]);
		i++;
	}
	if (s[i] == (char)c)
		return (&tmp[i]);
	return (NULL);
}
