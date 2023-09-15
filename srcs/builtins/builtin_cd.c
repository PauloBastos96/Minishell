/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:36:58 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/15 14:24:05 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Free old PWD and OLDPWD and update them with the new values*/
static	void	update_var(char	**env, char *var, char *value)
{
	char	*temp;

	free(*env);
	temp = ft_strdup(value);
	*env = ft_strjoin(var, temp);
	free(temp);
}

/*Get the old pwd, either the cuurent directory before changing
or empty if the PWD variable doesn't exist*/
char	*get_old_pwd(char ***env)
{
	char	*temp;
	char	*oldpwd;

	temp = ft_getenv("PWD", env);
	if (temp)
		oldpwd = ft_strdup(temp);
	else
		oldpwd = ft_strdup("");
	return (oldpwd);
}

/*Create OLDPWD variable if it doesn't exist*/
void	create_oldpwd(t_shell *shell, char *oldpwd)
{
	int		i;
	char	**new_env;
	char	**env;

	i = 0;
	env = shell->env;
	while (env[i])
		i++;
	new_env = ft_calloc(sizeof(char *), i + 2);
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = ft_strdup(oldpwd);
	free(shell->env);
	shell->env = new_env;
}

/*Update PWD and OLDPWD environment variables*/
void	update_pwd(t_shell *shell)
{
	char	*pwd;
	char	*oldpwd;
	char	**env;
	bool	has_old_pwd;
	int		i;

	i = 0;
	pwd = getcwd(NULL, 0);
	oldpwd = get_old_pwd(&shell->env);
	has_old_pwd = false;
	env = shell->env;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD", 3) == 0)
			update_var(&env[i], "PWD=", pwd);
		if (ft_strncmp(env[i], "OLDPWD", 6) == 0)
		{
			update_var(&env[i], "OLDPWD=", oldpwd);
			has_old_pwd = true;
		}
		i++;
	}
	if (!has_old_pwd)
		create_oldpwd(shell, oldpwd);
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
	if (ft_strncmp(path, "~", 1) == 0)
		path = get_home_path(path);
	if (chdir(path) == -1)
	{
		perror(NULL);
		return (1);
	}
	update_pwd(shell);
	return (0);
}
