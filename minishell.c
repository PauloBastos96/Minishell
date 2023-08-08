/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:24 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/08 13:01:42 by paulorod         ###   ########.fr       */
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
void	handle_builtins(t_cmd *cmd, char **env)
{
	add_history(cmd->cmd);
	if (ft_strncmp(cmd->cmd, "echo ", 5) == 0)
		ft_echo(cmd->cmd, cmd->output);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd(cmd->output);
	else if (ft_strncmp(cmd->cmd, "cd ", 3) == 0)
		ft_cd(cmd->cmd, env);
	else if (ft_strcmp(cmd->cmd, "clear") == 0)
		ft_clear();
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
	{
		free(cmd->cmd);
		rl_clear_history();
		exit(0);
	}
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
			handle_builtins(command, env);
		free(command);
	}
	(void)argc;
	(void)argv;
	return (0);
}
