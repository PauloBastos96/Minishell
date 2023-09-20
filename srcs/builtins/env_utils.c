/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:56:57 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/20 16:10:29 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

/*Sort enviroment variables by alphabetical order*/
char	**sort_envs(char **envs)
{
	bool	is_sorted;
	char	*temp;
	int		i;

	is_sorted = false;
	while (!is_sorted)
	{
		i = 0;
		is_sorted = true;
		while (envs[i])
		{
			if (envs[i + 1])
			{
				if (ft_strcmp(envs[i], envs[i + 1]) > 0)
				{
					temp = envs[i];
					envs[i] = envs[i + 1];
					envs[i + 1] = temp;
					is_sorted = false;
				}
			}
			i++;
		}
	}
	return (envs);
}

/*Check if enviroment already contains inputed variable*/
bool	is_duplicate(char **env, char *new)
{
	int	i;
	int	length;

	i = 0;
	while (env[i])
	{
		length = 0;
		while (new[length] && new[length] != '=')
			length++;
		if (!ft_strncmp(env[i], new, length))
			return (true);
		i++;
	}
	return (false);
}

/*Free old PWD and OLDPWD and update them with the new values*/
static void	update_var(char **env, char *var, char *value)
{
	char	*temp;

	free(*env);
	if (!value)
		*env = ft_strdup(var);
	else
	{
		temp = ft_strdup(value);
		*env = ft_strjoin(var, temp);
		free(temp);
	}
}

/*Update PWD and OLDPWD environment variables*/
void	update_pwd(char ***_env)
{
	char	*pwd;
	char	*oldpwd;
	char	**env;
	int		i;

	i = 0;
	env = *_env;
	pwd = getcwd(NULL, 0);
	oldpwd = get_old_pwd(_env);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD", 3) == 0)
			update_var(&env[i], "PWD=", pwd);
		else if (ft_strncmp(env[i], "OLDPWD", 6) == 0 && oldpwd)
			update_var(&env[i], "OLDPWD=", oldpwd);
		else if (ft_strncmp(env[i], "OLDPWD", 6) == 0 && !oldpwd)
			update_var(&env[i], "OLDPWD", oldpwd);
		i++;
	}
	free(pwd);
	free(oldpwd);
}
