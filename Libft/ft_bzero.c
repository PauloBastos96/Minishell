/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:33:18 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/20 20:06:56 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Erases 'n' bytes of memory starting at the location pointed by '*s'*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
