/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:00:41 by vpacheco          #+#    #+#             */
/*   Updated: 2023/09/20 16:18:53 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../minishell.h"

/*Check if command is a builtin*/
bool	is_builtin(t_cmd *cmd)
{
	cmd = set_quotes(cmd);
	if (!cmd->cmd[0])
		return (false);
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (true);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (true);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (true);
	return (false);
}

/*Builtin env command*/
int	ft_env(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;

	cmd = shell->cmd;
	if (cmd->cmd[1])
		return (1);
	if (!shell->env)
	{
		print_fd("Env doesn't exist", 2, NULL);
		return (1);
	}
	i = -1;
	while (shell->env[++i])
		print_fd(shell->env[i], STDOUT_FILENO, NULL);
	return (0);
}

/*Builtin pwd command*/
int	ft_pwd(t_shell *shell)
{
	char	*pwd;
	t_cmd	*cmd;

	cmd = shell->cmd;
	if (cmd->cmd[1])
	{
		print_fd("too many arguments", 2, "pwd");
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("Pwd error");
		return (1);
	}
	print_fd(pwd, STDOUT_FILENO, NULL);
	free(pwd);
	return (0);
}

/*Builtin exit command*/
int	ft_exit(t_shell *shell)
{
	int	exit_code;
	int	i;

	i = 0;
	print_fd("exit", 1, NULL);
	while (shell->cmd->cmd[i])
		i++;
	exit_code = get_exit_code(shell->cmd->cmd[1]);
	if (i > 2)
	{
		print_fd("too many arguments", 2, "minishell: exit");
		return (1);
	}
	free_all(shell);
	rl_clear_history();
	exit(exit_code);
}
