/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpacheco <vpacheco@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:00:41 by vpacheco          #+#    #+#             */
/*   Updated: 2023/08/02 17:47:51 by vpacheco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/list.h"

//builtin_fd "feito por ti"
int	ft_cd(t_cmd *cmd, char **env)
{
	char	*path;

	path = ft_strtrim(cmd->cmd, "cd ");
	if (ft_strncmp(path, "~", 1) == 0)
		path = get_home_path(path);
	if (chdir(path) == -1)
		perror(NULL);
	free(path);
}

//builtin env "eu vi o teu mas como já tinha este feito depois é só ver qual usamos"
int	env(t_cmd *cmd, char **env, int output)
{
	int i;
	
	if (cmd->cmd[1])
		return(1);
	if (!env)
	{
		print_fd("Env doesn't exist", 2, NULL);
		return(1);
	}
	i = -1;
	while (env[++i])
		print_fd(env[i], output, NULL);
	return(0);
}

//builtin echo
int echo(t_cmd *cmd, int output)
{
	int	i;

	i = 0 + (ft_strncmp("-n", cmd->cmd[1], 3) == 0);
	while (cmd->cmd[++i])
	{
		write(output, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		if (cmd->cmd[i + 1])
			write(output, " ", 1);
	}
	if (ft_strncmp("-n", cmd->cmd[1], 3))
		write(output, "\n", 1);
	return(0);
}

//builtin pwd
int ft_pwd(int output)
{
	char *pwd;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("Pwd error");
		return(1);
	}
	print_fd(pwd, output, NULL);
	free(pwd);
	return(0);
}
