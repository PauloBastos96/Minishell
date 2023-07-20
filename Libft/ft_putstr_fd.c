/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:50:19 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/19 11:50:33 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Outputs the string ’s’ to the given file descriptor*/
void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
