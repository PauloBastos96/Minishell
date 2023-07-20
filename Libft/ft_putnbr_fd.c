/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:25:53 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/24 12:11:38 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns number of digits in number 'n'*/
static int	count_digits(int n)
{
	int	digits;

	digits = 0;
	if (n < 0)
		n *= -1;
	while (n % 10 >= 1 || n > 9)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

/*Returns number 'nb' to the power of 'power'*/
static int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_recursive_power(nb, power - 1));
}

/*Deal with n <= 0*/
static void	deal_with_special_cases(int fd, int *n)
{
	if (*n == 0)
		write(fd, "0", 1);
	if (*n < 0)
	{
		write(fd, "-", 1);
		*n *= -1;
	}
}

/*Outputs the integer ’n’ to the given file descriptor*/
void	ft_putnbr_fd(int n, int fd)
{
	char	nbr;
	int		digits;
	int		i;

	nbr = 0;
	digits = count_digits(n);
	if (n == INT_MIN)
	{
		write(fd, "-2", 2);
		n = 147483648;
	}
	i = count_digits(n) - 1;
	deal_with_special_cases(fd, &n);
	while (n % 10 >= 1 || n > 9 || digits > 0)
	{
		nbr = n / ft_recursive_power(10, i) + '0';
		write(fd, &nbr, 1);
		n %= ft_recursive_power(10, i--);
		digits--;
	}
}
