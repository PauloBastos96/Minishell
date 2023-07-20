/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:40:01 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/24 11:50:22 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates memory for an array of 'nmemb' elements of 'size' bytes each.
And sets the bytes to null.
Returns  a  pointer to the allocated memory*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	if (nmemb * size > INT_MAX)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
