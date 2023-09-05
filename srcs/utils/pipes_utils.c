/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:22:57 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/08/24 14:01:11 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_pipes(char *cmd_str)
{
	if (ft_strnstr(cmd_str, "|", ft_strlen(cmd_str)))
		return (1);
	return (0);
}

int	check_valid_pipe(char *cmd_str)
{
	int	i;

	i = 0;
	while (cmd_str[i])
	{
		if (cmd_str[i] == '|')
		{
			if (cmd_str[i - 1] != ' ')
				return (0);
			if (cmd_str[i + 1] != ' ')
				return (0);
		}
		i++;
	}
	return (1);
}
