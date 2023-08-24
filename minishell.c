/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:24 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/24 15:02:16 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_using_sub_process = false;

/*Search PATH for command, or use direct path, and run it*/
int	run_command(t_cmd *cmd, char **env)
{
	if (ft_strchr(cmd->cmd[0], '/'))
		cmd->path = cmd->cmd[0];
	else
		cmd->path = search_command_path(cmd->cmd[0]);
	if (cmd->path)
		return (create_command_process(cmd, env));
	return (1);
}

/*Handle builtin and external commands*/
void	handle_commands(t_cmd *cmd, char ***env)
{
	if (!cmd->cmd[0])
		return ;
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		ft_echo(cmd, cmd->output);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		ft_pwd(cmd, cmd->output);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		ft_cd(cmd, env);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		ft_env(cmd, *env, cmd->output);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		ft_export(cmd, env);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		ft_unset(env, cmd);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		ft_exit(cmd);
	else
		run_command(cmd, *env);
}

/*Parse command into a t_cmd struct*/
//TODO create multiple structs when there are pipes
t_cmd	*command_parser(char *cmd_line, char ***env)
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
			cmd_struct->cmd = create_cmd(command, env);
			last_i = i + 1;
		}
		i++;
	}
	command = ft_substr(cmd_line, last_i, i);
	cmd_struct->cmd = create_cmd(command, env);
	cmd_struct->output = 1;
	free(command);
	free(cmd_line);
	return (cmd_struct);
}

//Main shell loop
//!readline has memory leaks that don't have to be fixed
void	shell_loop(char **env_array, char ***env)
{
	char	*command;
	t_cmd	*cmd;

	while (true)
	{
		command = readline(PROMPT);
		if (!command)
		{
			printf("exit\n");
			exit(0);
		}
		if (*command)
		{
			add_history(command);
			if (ft_strlen(command) > 0)
				cmd = command_parser(command, env);
			handle_commands(cmd, &env_array);
			free_cmd(cmd);
		}
	}
}

//Start shell
//!env should remain const because it should never be modified by us
int	main(int argc, char **argv, const char **env)
{
	char	**env_array;

	register_signals();
	env_array = fill_envs(env);
	shell_loop(env_array, &env_array);
	(void)argc;
	(void)argv;
	return (0);
}
