/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:55:34 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/24 11:52:00 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Checks if character is alphabetical.
Returns 1 if true and 0 if false.*/
int	ft_isalpha(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else
		return (0);
}
