/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:48:27 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/17 11:33:50 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Convert letter to lowercase.
Returns lowercase letter or the provided character if it failed*/
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
