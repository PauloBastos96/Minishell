/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:22:57 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/13 13:43:41 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../includes/shell.h"

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

void	free_all(t_shell *shell)
{
	free_cmd(shell->cmd);
	free_envs(shell);
	free(shell);
}
