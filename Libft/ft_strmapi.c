/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:25:14 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/17 23:34:29 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Applies the function ’f’ to each character of the string ’s’,
and passing its index as first argument to create a new string
resulting from successive applications of ’f’*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*f_string;

	i = 0;
	f_string = ft_strdup(s);
	if (!f_string)
		return (0);
	while (s[i])
	{
		f_string[i] = f(i, f_string[i]);
		i++;
	}
	return (f_string);
}
