/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:49:13 by paulorod          #+#    #+#             */
/*   Updated: 2023/07/21 16:22:06 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Builtin cd command*/
void	ft_cd(char *command)
{
	char	*path;

	path = ft_strtrim(command, "cd ");
	if (chdir(path) == -1)
		perror(NULL);
	free(path);
}
