/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:36:58 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/22 15:36:40 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Get the old pwd, either the current directory before changing
or empty if the PWD variable doesn't exist*/
static char	*get_old_pwd(char ***env)
{
	char	*temp;
	char	*oldpwd;

	temp = ft_getenv("PWD", env);
	if (temp)
		oldpwd = ft_strdup(temp);
	else
		oldpwd = NULL;
	return (oldpwd);
}

/*Free old PWD and OLDPWD and update them with the new values*/
static void	update_var(char	**env, char *var, char *value)
{
	char	*temp;

	free(*env);
	if (value)
	{
		temp = ft_strdup(value);
		*env = ft_strjoin(var, temp);
		free(temp);
	}
	else
		*env = NULL;
}

/*Update PWD and OLDPWD environment variables*/
static void	update_pwd(t_shell *shell)
{
	char	*pwd;
	char	*oldpwd;
	char	**env;
	int		i;

	i = 0;
	pwd = getcwd(NULL, 0);
	oldpwd = get_old_pwd(&shell->env);
	env = shell->env;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD", 3) == 0)
			update_var(&env[i], "PWD=", pwd);
		if (ft_strncmp(env[i], "OLDPWD", 6) == 0 && oldpwd)
			update_var(&env[i], "OLDPWD=", oldpwd);
		else if (ft_strncmp(env[i], "OLDPWD", 6) == 0 && !oldpwd)
			update_var(&env[i], "OLDPWD", NULL);
		i++;
	}
	free(pwd);
	free(oldpwd);
}

/*Builtin cd command*/
int	ft_cd(t_shell *shell)
{
	char	*path;

	path = shell->cmd->cmd[1];
	if (!path)
		path = get_home_path(ft_strdup("~"));
	else
		path = ft_strdup(path);
	if (ft_strncmp(path, "~", 1) == 0)
		path = get_home_path(path);
	if (chdir(path) == -1)
	{
		free(path);
		perror(NULL);
		return (1);
	}
	free(path);
	update_pwd(shell);
	return (0);
}
