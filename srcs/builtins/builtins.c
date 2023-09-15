/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:00:41 by vpacheco          #+#    #+#             */
/*   Updated: 2023/09/15 13:05:50 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/list.h"
#include "../../minishell.h"

/*Builtin cd command*/
int	ft_cd(t_shell *shell)
{
	char	*path;

	path = shell->cmd->cmd[1];
	if (!path)
		path = get_home_path(ft_strdup("~"));
	if (ft_strncmp(path, "~", 1) == 0)
		path = get_home_path(path);
	if (chdir(path) == -1)
	{
		perror(NULL);
		return (1);
	}
	update_pwd(&shell->env);
	return (0);
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
