/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:24 by paulorod          #+#    #+#             */
/*   Updated: 2023/07/21 13:52:38 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_builtins(char *command)
{
	add_history(command);
	if (ft_strncmp(command, "echo ", 5) == 0)
		ft_echo(command);
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
