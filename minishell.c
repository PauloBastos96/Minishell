/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:24 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/08 16:09:58 by paulorod         ###   ########.fr       */
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
//TODO clear cmd struct on exit
//TODO send echo, env and pwd to correct outputs
void	handle_builtins(t_cmd *cmd, char **env)
{
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		ft_echo(cmd, 1);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		ft_pwd(1);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd->cmd[0], "clear") == 0)
		ft_clear();
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		ft_env(cmd, env, 1);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
	{
		free(cmd->cmd);
		rl_clear_history();
		exit(0);
	}
}

/*Create command struct*/
char	**create_cmd(char *command)
{
	char			**cmd;
	int				pos;
	size_t			i;
	unsigned int	j;

	cmd = alloc_cmd(command);
	i = 0;
	j = 0;
	pos = 0;
	while (command[i])
	{
		if (command[i] == ' ')
		{
			cmd[pos] = ft_substr(command, j, i - j);
			pos++;
			j = i + 1;
		}
		else if (!command[i + 1])
		{
			cmd[pos] = ft_substr(command, j, i + 1 - j);
			j = i + 1;
		}
		i++;
	}
	return (cmd);
}

/*Parse command into a t_cmd struct*/
//TODO create multiple structs when there are pipes
t_cmd	*command_parser(char *cmd_line)
{
	t_cmd	*cmd_struct;
	char	*command;
	int		i;
	int		last_i;

	i = 0;
	last_i = 0;
	cmd_struct = ft_calloc(sizeof(t_cmd), 1);
	while (cmd_line[i])
	{
		if (cmd_line[i] == '|')
		{
			command = ft_substr(cmd_line, last_i, i - 1);
			cmd_struct->cmd = create_cmd(command);
			last_i = i + 1;
		}
		i++;
	}
	command = ft_substr(cmd_line, last_i, i);
	cmd_struct->cmd = create_cmd(command);
	return (cmd_struct);
}

//Start shell
//!readline has memory leaks that don't have to be fixed
int	main(int argc, char **argv, char **env)
{
	char	*command;
	t_cmd	*cmd;

	while (true)
	{
		command = readline(PROMPT);
		add_history(command);
		if (ft_strlen(command) > 0)
			cmd = command_parser(command);
		handle_builtins(cmd, env);
		free(command);
	}
	(void)argc;
	(void)argv;
	return (0);
}
