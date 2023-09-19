/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:25:09 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/19 14:26:17 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Close file descriptor*/
int	close_safe(int *fd)
{
	int	result;

	if (*fd == -1)
		return (0);
	result = close(*fd);
	if (result == 0)
		*fd = -1;
	return (result);
}

/*Swap file descriptor*/
void	swap_fd(int *fd, int target)
{
	close_safe(fd);
	*fd = target;
}
