/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:49:20 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/11 13:07:33 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/list.h"
#include "../../includes/builtins.h"
#include "../../minishell.h"

/*Builtin exit command*/
void	ft_exit(t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->cmd[1])
	{
		if (is_exit_code_valid(cmd->cmd[1]))
			exit_code = ft_atoi(cmd->cmd[1]);
		else
		{
			printf("exit: %s: numeric argument required\n", cmd->cmd[1]);
			return ;
		}
	}
	free(cmd->cmd);
	rl_clear_history();
	exit(exit_code);
}
