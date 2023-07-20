/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:44:32 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/24 16:54:50 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns number 'nb' to the power of 'power'*/
static int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_recursive_power(nb, power - 1));
}

/*Returns number of digits in number 'n'*/
static int	count_digits(int n)
{
	int	digits;

	digits = 0;
	if (n == INT_MIN)
		return (10);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

/*Handle negative numbers*/
static void	handle_negatives(int n, char *string, int digits)
{
	int	start;
	int	counter;
	int	i;

	i = 1;
	if (n == INT_MIN)
	{
		n = 147483648;
		digits = 10;
	}
	else
		n *= -1;
	string[0] = '-';
	counter = digits - 1;
	start = n;
	while (i <= digits)
	{
		string[i] = (n / ft_recursive_power(10, counter)) + '0';
		n %= ft_recursive_power(10, counter--);
		i++;
	}
	if (start == 147483648)
		string[1] = '2';
	string[i] = 0;
}

/*Handle positive numbers*/
static void	handle_positives(int n, char *string, int digits)
{
	int	counter;
	int	i;

	i = 0;
	counter = digits - 1;
	while (i < digits)
	{
		string[i] = (n / ft_recursive_power(10, counter)) + '0';
		n %= ft_recursive_power(10, counter--);
		i++;
	}
	string[i] = 0;
}

/*Allocates and returns a string representing the int received as an argument.*/
char	*ft_itoa(int n)
{
	char	*string;
	int		digits;

	digits = count_digits(n);
	if (n > 0)
		string = (char *)malloc(digits + 1);
	else
		string = (char *)malloc(digits + 2);
	if (!string)
		return (0);
	if (n == 0)
	{
		string[0] = '0';
		string[1] = 0;
	}
	if (n < 0)
		handle_negatives(n, string, digits);
	else if (n > 0)
		handle_positives(n, string, digits);
	return (string);
}
