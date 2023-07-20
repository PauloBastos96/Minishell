/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:47:30 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/19 11:41:48 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Outputs the character ’c’ to the given file descriptor.*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
