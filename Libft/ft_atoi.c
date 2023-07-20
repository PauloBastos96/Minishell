/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:32:01 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/19 20:45:12 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Check if the character is a number*/
static int	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*Set appropriate sign*/
static int	set_sign(char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
}

/*Check if charcter can be skipped*/
static int	is_skippable(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || \
		c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

/*Parse string to int*/
int	ft_atoi(const char *nptr)
{
	int		final_number;
	int		sign;
	int		i;

	i = 0;
	final_number = 0;
	while (is_skippable(nptr[i]))
		i++;
	sign = set_sign(nptr[i]);
	if (sign == -1 || nptr[i] == '+')
		i++;
	while (is_number((nptr[i])))
	{
		final_number = 10 * final_number + (nptr[i] - '0');
		i++;
	}
	return (final_number * sign);
}
