/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:33:12 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/12 14:45:51 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Returns the length of a string.*/
unsigned int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
