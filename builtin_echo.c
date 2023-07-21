/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:09:54 by paulorod          #+#    #+#             */
/*   Updated: 2023/07/21 13:57:46 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO This is working for simple text after the command
//TODO but it still needs to handle content from variables/files
/*Builtin echo command*/
void	ft_echo(char *command)
{
	int	i;

	i = 5;
	while (command[i] == ' ')
		i++;
	while (command[i])
	{
		write(1, &command[i], 1);
		i++;
	}
}
