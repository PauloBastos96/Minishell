/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:00:41 by vpacheco          #+#    #+#             */
/*   Updated: 2023/09/11 14:58:39 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/list.h"
#include "../../includes/builtins.h"
#include "../../minishell.h"

/*Builtin cd command*/
int	ft_cd(t_shell *shell)
{
	char	*path;

	path = shell->cmd->cmd[1];
	if (!path)
		return (1);
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

/*Builtin echo command*/
int	ft_echo(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;

	cmd = shell->cmd;
	if (!cmd->cmd[1])
		return (0);
	i = 0 + (ft_strncmp("-n", cmd->cmd[1], 3) == 0);
	while (cmd->cmd[++i])
	{
		write(1, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		if (cmd->cmd[i + 1])
			write(1, " ", 1);
	}
	if (ft_strncmp("-n", cmd->cmd[1], 3))
		write(1, "\n", 1);
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
int	ft_exit(t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->cmd[1])
	{
		if (is_exit_code_valid(cmd->cmd[1]))
			exit_code = ft_atoi(cmd->cmd[1]);
		else
		{
			printf("exit: %s: numeric argument required\n", cmd->cmd[1]);
			return (1);
		}
	}
	free_cmd(cmd);
	rl_clear_history();
	exit(exit_code);
}
