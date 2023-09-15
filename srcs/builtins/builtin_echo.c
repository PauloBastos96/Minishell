/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:05:12 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/15 13:05:43 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Check if the -n argument is valid*/
static bool	is_n_arg_valid(char *arg)
{
	int		i;
	bool	valid;

	i = 0;
	valid = true;
	if (*arg != '-')
		return (false);
	if (!arg[1])
		return (false);
	while (arg[++i])
	{
		if (arg[i] != 'n')
			valid = false;
	}
	return (valid);
}

/*Builtin echo command*/
int	ft_echo(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;

	cmd = shell->cmd;
	if (!cmd->cmd[1])
		return (0);
	i = 0;
	if (is_n_arg_valid(cmd->cmd[1]))
		i = 1;
	while (cmd->cmd[++i])
	{
		write(1, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		if (cmd->cmd[i + 1])
			write(1, " ", 1);
	}
	if (!is_n_arg_valid(cmd->cmd[1]))
		write(1, "\n", 1);
	return (0);
}
