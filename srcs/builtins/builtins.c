/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:00:41 by vpacheco          #+#    #+#             */
/*   Updated: 2023/08/11 16:04:45 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/list.h"
#include "../../includes/builtins.h"
#include "../../minishell.h"

//Builtin cd command
int	ft_cd(t_cmd *cmd)
{
	char	*path;

	path = cmd->cmd[1];
	if (!path)
		return (1);
	if (ft_strncmp(path, "~", 1) == 0)
		path = get_home_path(path);
	if (chdir(path) == -1)
	{
		perror(NULL);
		return (1);
	}
	return (0);
}

//Builtin env command
//"eu vi o teu mas como já tinha
//este feito depois é só ver qual usamos"
int	ft_env(t_cmd *cmd, const char **env, int output)
{
	int	i;

	if (cmd->cmd[1])
		return (1);
	if (!env)
	{
		print_fd("Env doesn't exist", 2, NULL);
		return (1);
	}
	i = -1;
	while (env[++i])
		print_fd((char *)env[i], output, NULL);
	return (0);
}

/*Builtin echo command*/
int	ft_echo(t_cmd *cmd, int output)
{
	int	i;

	if (!cmd->cmd[1])
		return (0);
	i = 0 + (ft_strncmp("-n", cmd->cmd[1], 3) == 0);
	while (cmd->cmd[++i])
	{
		write(output, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		if (cmd->cmd[i + 1])
			write(output, " ", 1);
	}
	if (ft_strncmp("-n", cmd->cmd[1], 3))
		write(output, "\n", 1);
	return (0);
}

/*Builtin pwd command*/
int	ft_pwd(t_cmd *cmd, int output)
{
	char	*pwd;

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
	print_fd(pwd, output, NULL);
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
	free(cmd->cmd);
	rl_clear_history();
	exit(exit_code);
}
