/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:07:26 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/11 14:23:39 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Checks if character is a number.
Returns 1 if true and 0 if false.*/
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
