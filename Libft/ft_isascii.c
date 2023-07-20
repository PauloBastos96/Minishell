/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:18:01 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/11 14:23:32 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Checks if character fits in the ASCII table.
Returns 1 if true and 0 if false.*/
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
