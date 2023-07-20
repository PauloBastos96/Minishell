/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percentage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:39:47 by paulorod          #+#    #+#             */
/*   Updated: 2023/05/25 14:17:03 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Print percentage sign on string without parameters*/
int	ft_print_percentage(char *s)
{
	int	i;
	int	w_bytes;

	i = 0;
	w_bytes = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1] == '%')
		{
			w_bytes += ft_print_char(s[i]);
			i++;
		}
		else
			w_bytes += ft_print_char(s[i]);
		i++;
	}
	return (w_bytes);
}

/*Print percentage sign on string with parameters*/
void	ft_print_percentage_arg(char *fmt, int *w_bytes, int *i)
{
	if (fmt[*i] == '%' && fmt[*i + 1] == '%')
	{
		*w_bytes += ft_print_char(fmt[*i]);
		*i += 1;
	}
}
