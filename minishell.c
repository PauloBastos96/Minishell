/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpacheco <vpacheco@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:24 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/02 17:53:37 by vpacheco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Handle builtin commands*/
void	handle_builtins(t_cmd *cmd)
{
	add_history(cmd->cmd);
	if (ft_strncmp(cmd->cmd, "echo ", 5) == 0)
		ft_echo(cmd->cmd, cmd->output);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd->cmd)) == 0)
		ft_pwd(cmd->output);
	else if (ft_strncmp(cmd->cmd, "cd ", 3) == 0)
		ft_cd(cmd->cmd);
	else if (ft_strncmp(cmd->cmd, "clear", ft_strlen(cmd->cmd)) == 0)
		ft_clear();
	else if (ft_strncmp(cmd->cmd, "exit", ft_strlen(cmd->cmd)) == 0)
	{
		free(cmd->cmd);
		rl_clear_history();
		exit(0);
	}
}

//Start shell
//!readline has memory leaks that don't have to be fixed
int	main(void)
{
	char	*command;

	while (true)
	{
		command = readline(PROMPT);
		if (ft_strlen(command) > 0)
			handle_builtins(command);
		free(command);
	}
	if (command)
		free(command);
	return (0);
}
