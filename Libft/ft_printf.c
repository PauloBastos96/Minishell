/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:36:32 by paulorod          #+#    #+#             */
/*   Updated: 2023/05/25 14:07:07 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Print invalid formats as normal string*/
static void	ft_print_invalid_format(char *fmt, int *w_bytes, int *i)
{
	if (fmt[*i] == '%' && !is_format_char(fmt[*i + 1]) && fmt[*i + 1] != '%'
		&& fmt[*i - 1] != '%')
	{
		*w_bytes += ft_print_char(fmt[*i]);
		*i += 1;
		*w_bytes += ft_print_char(fmt[*i]);
		*i += 1;
	}
	else if (fmt[*i] == '%' && is_format_char(fmt[*i + 1])
		&& fmt[*i - 1] == '%' && fmt[*i - 2] != '%')
	{
		*w_bytes += ft_print_char(fmt[*i + 1]);
		*i += 1;
	}
}

/*Print acording to format*/
static int	ft_print_parse(int expected_args, char *fmt, va_list args)
{
	int	i;
	int	w_bytes;

	i = 0;
	w_bytes = 0;
	while (expected_args--)
	{
		while (fmt[i])
		{
			ft_print_percentage_arg(fmt, &w_bytes, &i);
			if (fmt[i] != '%')
			{
				if ((fmt[i - 1] != '%' && is_format_char(fmt[i]))
					|| !is_format_char(fmt[i]))
						w_bytes += ft_print_char(fmt[i]);
			}
			ft_print_invalid_format(fmt, &w_bytes, &i);
			w_bytes += ft_print_formats(fmt, i, args);
			i++;
		}
	}
	return (w_bytes);
}

/*Format and print data*/
int	ft_printf(const char *format, ...)
{
	int		expected_args;
	va_list	args;

	va_start(args, format);
	expected_args = valid_formats((char *)format);
	if (!ft_strchr(format, '%'))
		return (ft_print_string((char *)format));
	else if (!expected_args)
		return (ft_print_percentage((char *)format));
	return (ft_print_parse(expected_args, (char *)format, args));
}
