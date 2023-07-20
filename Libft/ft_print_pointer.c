/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:13:21 by paulorod          #+#    #+#             */
/*   Updated: 2023/05/25 14:17:47 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Remove null bytes from the begining of the adress*/
static char	*clean_adress(char *adress)
{
	int		i;
	int		k;
	int		j;
	char	*c_adress;

	i = 19;
	k = 0;
	j = 0;
	c_adress = ft_calloc(sizeof(char), 19);
	while (j < 19)
	{
		if (adress[j])
		{
			c_adress[k++] = adress[j];
			i++;
		}
		j++;
	}
	free(adress);
	return (c_adress);
}

/*Convert pointer adress to decimal and then to hexadecimal
and finally convert it to a string*/
int	ft_print_pointer(void *ptr)
{
	uintptr_t	d_adress;
	char		*adress;
	char		*c_adress;
	int			w_bytes;
	int			i;

	d_adress = (uintptr_t)ptr;
	if (!d_adress)
		return (ft_print_string("(nil)"));
	adress = ft_calloc(sizeof(char), 19);
	if (!adress)
		return (0);
	i = 18;
	while (d_adress > 0 && i > 1)
	{
		adress[i] = "0123456789abcdef"[d_adress % 16];
		d_adress /= 16;
		i--;
	}
	adress[i--] = 'x';
	adress[i] = '0';
	c_adress = clean_adress(adress);
	w_bytes = ft_print_string(c_adress);
	free(c_adress);
	return (w_bytes);
}
