/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:24 by paulorod          #+#    #+#             */
/*   Updated: 2023/07/20 16:32:19 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_builtins(char *command)
{
	if (ft_strncmp(command, "echo", ft_strlen(command)) == 0)
		ft_echo(command);
	else if (ft_strncmp(command, "cd", ft_strlen(command)) == 0)
		ft_cd(command);
	else if (ft_strncmp(command, "pwd", ft_strlen(command)) == 0)
		ft_pwd(command);
	else if (ft_strncmp(command, "export", ft_strlen(command)) == 0)
		ft_export(command);
	else if (ft_strncmp(command, "unset", ft_strlen(command)) == 0)
		ft_unset(command);
	else if (ft_strncmp(command, "env", ft_strlen(command)) == 0)
		ft_env(command);
	else if (ft_strncmp(command, "exit", ft_strlen(command)) == 0)
	{
		free(command);
		exit(0);
	}
	else
		ft_exec(command);
}

//Start shell
//!readline has memory leaks that don't have to be fixed
int	main(void)
{
	char	*command;

	while (true)
	{
		command = readline(PROMPT);
		if (ft_strncmp(command, "exit", ft_strlen(command)) == 0)
			break ;
		printf("%s\n", command);
		free(command);
	}
	if (command)
		free(command);
	return (0);
}
