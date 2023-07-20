/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:18:44 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/17 11:33:45 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Convert letter to uppercase.
Returns uppercase letter or the provided character if it failed*/
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
