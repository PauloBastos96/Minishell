/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formats.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:14:53 by paulorod          #+#    #+#             */
/*   Updated: 2023/05/25 14:12:27 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Check if character is a valid format*/
int	is_format_char(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X')
		return (1);
	return (0);
}

/*Count the amount of valid formats*/
int	valid_formats(char *format)
{
	int	i;
	int	val_formats;

	i = 0;
	val_formats = 0;
	while (format[i])
	{
		if (format[i] == '%' && is_format_char(format[i + 1]))
			val_formats++;
		i++;
	}
	return (val_formats);
}

/*Print according to detected format*/
int	ft_print_formats(char *fmt, int i, va_list args)
{
	int	w_bytes;

	w_bytes = 0;
	if (fmt[i] == '%' && fmt[i + 1] == 'c')
		w_bytes += ft_print_char(va_arg(args, int));
	if (fmt[i] == '%' && fmt[i + 1] == 's')
		w_bytes += ft_print_string(va_arg(args, char *));
	if (fmt[i] == '%' && (fmt[i + 1] == 'i' || fmt[i + 1] == 'd'))
		w_bytes += ft_print_int(va_arg(args, int));
	if (fmt[i] == '%' && fmt[i + 1] == 'u')
		w_bytes += ft_print_uint(va_arg(args, int));
	if (fmt[i] == '%' && fmt[i + 1] == 'p')
		w_bytes += ft_print_pointer(va_arg(args, void *));
	if (fmt[i] == '%' && fmt[i + 1] == 'x')
		w_bytes += ft_print_hex(va_arg(args, int), "0123456789abcdef");
	if (fmt[i] == '%' && fmt[i + 1] == 'X')
		w_bytes += ft_print_hex(va_arg(args, int), "0123456789ABCDEF");
	return (w_bytes);
}
