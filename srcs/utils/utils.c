/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:59:38 by vpacheco          #+#    #+#             */
/*   Updated: 2023/08/10 16:17:41 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../minishell.h"

//Print error to fd
int	print_fd(char *error, char fd, char *name)
{
	if (name)
	{
		write(fd, name, ft_strlen(name));
		write(fd, ": ", 2);
	}
	write(fd, error, ft_strlen(error));
	write(fd, "\n", 1);
	return (1);
}

/*Allocate memory for the command struct*/
char	**alloc_cmd(char *command)
{
	char	**cmd;
	int		size;
	int		i;

	size = 1;
	i = 0;
	while (command[i])
	{
		if (command[i] == ' ')
			size++;
		i++;
	}
	cmd = ft_calloc(sizeof(cmd), size + 1);
	return (cmd);
}
