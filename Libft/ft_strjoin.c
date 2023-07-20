/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:59:08 by paulorod          #+#    #+#             */
/*   Updated: 2023/05/02 13:18:08 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates and returns a new string,
which is the result of the concatenation of ’s1’ and ’s2’*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		t_size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	t_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *)malloc(t_size);
	if (!join)
		return (NULL);
	while (s1[i])
		join[j++] = s1[i++];
	i = 0;
	while (s2[i])
		join[j++] = s2[i++];
	join[j] = '\0';
	return (join);
}
