/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:47:34 by paulorod          #+#    #+#             */
/*   Updated: 2023/05/25 14:14:58 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Remove null bytes from the begining of the adress*/
static char	*clean_string(char *string, int digits)
{
	int		i;
	int		j;
	char	*c_string;

	i = 0;
	j = 0;
	c_string = ft_calloc(sizeof(char), digits + 1);
	while (j < digits)
	{
		if (string[j])
			c_string[i++] = string[j];
		j++;
	}
	free(string);
	return (c_string);
}

/*Returns number of digits in number 'n'*/
static int	ft_printf_count_digits(unsigned int n)
{
	int	digits;

	digits = 0;
	if (n == UINT_MAX)
		return (10);
	while (n > 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

/*Convert decimal number to hexadecimal*/
int	ft_print_hex(unsigned int nbr, char *base)
{
	char	*string;
	int		w_bytes;
	int		digits;
	int		i;

	digits = ft_printf_count_digits(nbr);
	w_bytes = 0;
	if (digits == 0)
		return (ft_print_string("0"));
	string = ft_calloc(sizeof(char), digits + 1);
	if (!string)
		return (0);
	i = digits;
	string[i--] = '\0';
	while (nbr > 0)
	{
		string[i--] = base[nbr % 16];
		nbr /= 16;
	}
	string = clean_string(string, digits);
	i = 0;
	while (string[i])
		w_bytes += ft_print_char(string[i++]);
	free(string);
	return (w_bytes);
}
