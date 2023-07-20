/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:13:32 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/24 12:13:07 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns a pointer to a duplicate of string '*s'*/
char	*ft_strdup(const char *s)
{
	char	*duplicate;
	int		i;
	int		string_size;

	i = 0;
	string_size = ft_strlen((char *)s);
	duplicate = malloc((string_size + 1) * sizeof(char));
	if (!duplicate)
		return (NULL);
	while (s[i])
	{
		duplicate[i] = s[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}
