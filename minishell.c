/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:24 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/25 12:36:40 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"
#include "minishell.h"

bool	g_using_sub_process = false;

/*Search PATH for command, or use direct path, and run it*/
int	run_command(t_shell *shell)
{
	if (ft_strchr(shell->cmd->cmd[0], '/'))
		shell->cmd->path = ft_strdup(shell->cmd->cmd[0]);
	else
		shell->cmd->path = search_command_path(shell->cmd->cmd[0], shell);
	if (shell->cmd->path)
		return (create_command_process(shell->cmd, shell->env));
	return (127);
}

/*Handle builtin and external commands*/
void	handle_commands(t_shell *shell)
{
	char	*trimmed;

	trimmed = remove_quotes(shell->cmd->cmd[0]);
	free(shell->cmd->cmd[0]);
	shell->cmd->cmd[0] = trimmed;
	if (!shell->cmd->cmd[0] || !*(shell->cmd->cmd[0]))
		return ;
	if (ft_strcmp(shell->cmd->cmd[0], "echo") == 0)
		shell->status = ft_echo(shell);
	else if (ft_strcmp(shell->cmd->cmd[0], "pwd") == 0)
		shell->status = ft_pwd(shell);
	else if (ft_strcmp(shell->cmd->cmd[0], "cd") == 0)
		shell->status = ft_cd(shell);
	else if (ft_strcmp(shell->cmd->cmd[0], "env") == 0)
		shell->status = ft_env(shell);
	else if (ft_strcmp(shell->cmd->cmd[0], "export") == 0)
		shell->status = ft_export(shell);
	else if (ft_strcmp(shell->cmd->cmd[0], "unset") == 0)
		shell->status = ft_unset(shell);
	else if (ft_strcmp(shell->cmd->cmd[0], "exit") == 0)
		shell->status = ft_exit(shell);
	else
		shell->status = run_command(shell);
}

/*Parse command into a t_cmd struct*/
t_cmd	*command_parser(char *cmd_line, t_shell *shell)
{
	t_cmd	*cmd_struct;
	char	**tokens;
	int		i;

	i = 0;
	tokens = create_cmd_tokens(cmd_line, shell);
	cmd_struct = create_cmd_list(tokens);
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	return (cmd_struct);
}

// Start shell
//! env should remain const because it should never be modified by us
int	main(int argc, char **argv, const char **env)
{
	t_shell	*shell;

	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
	{
		print_fd("[FATAL]: malloc error", STDERR_FILENO, NULL);
		exit(1);
	}
	shell->status = 0;
	register_signals();
	shell->env = fill_envs(env);
	if (!shell->env)
	{
		print_fd("[FATAL]: malloc error", STDERR_FILENO, NULL);
		free(shell);
		exit(1);
	}
	shell_loop(shell);
	(void)argc;
	(void)argv;
	return (0);
}
