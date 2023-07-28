/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:24 by paulorod          #+#    #+#             */
/*   Updated: 2023/07/28 16:00:24 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Search PATH for command, or use direct path, and run it*/
void	run_command(char *cmd, char **env)
{
	if (execve(cmd, (char *const *)"-l", env) == -1)
		perror(NULL);
}

/*Handle builtin commands*/
void	handle_builtins(char *command, t_list **env_lst, char **env)
{
	add_history(command);
	if (ft_strncmp(command, "echo ", 5) == 0)
		ft_echo(command);
	else if (ft_strcmp(command, "pwd") == 0)
		ft_pwd();
	else if (ft_strncmp(command, "cd ", 3) == 0)
		ft_cd(command);
	else if (ft_strcmp(command, "clear") == 0)
		ft_clear();
	else if (ft_strcmp(command, "env") == 0)
		ft_env(env_lst);
	else if (ft_strcmp(command, "exit") == 0)
	{
		free(command);
		clear_env_list(env_lst);
		rl_clear_history();
		exit(0);
	}
	else
		run_command(command, env);
}

//Start shell
//!readline has memory leaks that don't have to be fixed
int	main(int argc, char **argv, char **env)
{
	char			*command;
	static t_list	**env_list;

	env_list = new_env_list(env);
	while (true)
	{
		command = readline(PROMPT);
		if (ft_strlen(command) > 0)
			handle_builtins(command, env_list, env);
		free(command);
	}
	(void)argc;
	(void)argv;
	return (0);
}
