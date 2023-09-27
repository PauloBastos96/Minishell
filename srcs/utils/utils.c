/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:59:38 by vpacheco          #+#    #+#             */
/*   Updated: 2023/09/27 11:59:00 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../minishell.h"

//Print error to fd
int	print_fd(char *error, char fd, char *name)
{
	if (name)
	{
		write(fd, name, ft_strlen(name));
		write(fd, ": ", 2);
	}
	write(fd, error, ft_strlen(error));
	write(fd, "\n", 1);
	return (1);
}

/*Allocate memory for the command struct*/
char	**alloc_cmd(char *command)
{
	char	**cmd;
	int		size;
	int		i;

	size = 1;
	i = 0;
	while (command[i])
	{
		if (command[i] == ' ')
			size++;
		i++;
	}
	cmd = ft_calloc(sizeof(cmd), size + 1);
	if (!cmd)
		return (NULL);
	return (cmd);
}

/*Fill array with envs*/
char	**fill_envs(const char **env)
{
	int		i;
	char	**array;

	i = 0;
	while (env[i])
		i++;
	array = ft_calloc(sizeof(array), i + 1);
	if (!array)
		return (NULL);
	i = 0;
	while (env[i])
	{
		array[i] = ft_strdup(env[i]);
		i++;
	}
	return (array);
}

/*Custom getenv function that searches our environment variable list*/
char	*ft_getenv(const char *name, char ***_env)
{
	int		i;
	char	*value;
	char	**env;

	i = 0;
	env = *_env;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, 
				ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '='))) == 0)
		{
			value = ft_strchr(env[i], '=');
			if (value)
				return (value + 1);
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
}

/*Get exit code or exit due to invalid argument*/
int	get_exit_code(t_shell *shell)
{
	int	exit_code;

	exit_code = 0;
	if (shell->cmd->cmd[1])
	{
		if (is_exit_code_valid(shell->cmd->cmd[1]))
			exit_code = ft_atoi(shell->cmd->cmd[1]);
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", 
				shell->cmd->cmd[1]);
			free_all(shell);
			exit(2);
		}
	}
	return (exit_code);
}
