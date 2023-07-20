/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:26:35 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/11 14:28:56 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Checks if character is printable.
Returns 1 if true and 0 if false.*/
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
