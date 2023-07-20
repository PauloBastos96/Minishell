/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:08:18 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/19 20:28:18 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns a pointer to the last occurence of the provided character 'c'*/
char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		found;
	char	*last;
	char	*tmp;

	i = 0;
	found = 0;
	tmp = (char *)s;
	while (tmp[i])
	{
		if (tmp[i] == (char)c)
		{
			found = 1;
			last = &tmp[i];
		}
		i++;
	}
	if (tmp[i] == (char)c)
		return (&tmp[i]);
	else if (found)
		return (last);
	else
		return (NULL);
}
