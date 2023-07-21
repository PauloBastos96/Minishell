/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:24 by paulorod          #+#    #+#             */
/*   Updated: 2023/07/21 16:20:03 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Handle builtin commands*/
void	handle_builtins(char *command)
{
	add_history(command);
	if (ft_strncmp(command, "echo ", 5) == 0)
		ft_echo(command);
	else if (ft_strncmp(command, "pwd", ft_strlen(command)) == 0)
		ft_pwd();
	else if (ft_strncmp(command, "cd ", 3) == 0)
		ft_cd(command);
	else if (ft_strncmp(command, "clear", ft_strlen(command)) == 0)
		ft_clear();
	else if (ft_strncmp(command, "exit", ft_strlen(command)) == 0)
	{
		free(command);
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
