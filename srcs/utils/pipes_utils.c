/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:22:57 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/19 14:41:17 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../includes/shell.h"

/*Check for pipes*/
int	check_pipes(char *cmd_str)
{
	if (ft_strnstr(cmd_str, "|", ft_strlen(cmd_str)))
		return (1);
	return (0);
}

/*Check if pipe is valid*/
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

/*Close std in and std out*/
void	close_std(t_cmd *cmd)
{
	close_safe(&cmd->std.out);
	close_safe(&cmd->std.in);
}
