/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:49:34 by paulorod          #+#    #+#             */
/*   Updated: 2023/05/25 14:16:32 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns number of digits in number 'n'*/
static int	ft_printf_count_digits(long n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n == LONG_MIN)
	{
		digits += 2;
		n = 223372036854775808;
	}
	if (n < 0)
	{
		n *= -1;
		digits++;
	}
	while (n % 10 >= 1 || n > 9)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

/*Print ints*/
int	ft_print_int(int nbr)
{
	int		w_bytes;

	ft_putnbr_fd(nbr, 1);
	w_bytes = ft_printf_count_digits(nbr);
	return (w_bytes);
}

/*Print unsigned ints*/
int	ft_print_uint(int nbr)
{
	int				w_bytes;
	unsigned int	u_nbr;

	u_nbr = (unsigned int)nbr;
	ft_putnbr_fd(u_nbr, 1);
	w_bytes = ft_printf_count_digits(u_nbr);
	return (w_bytes);
}
