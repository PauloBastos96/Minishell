/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:59:38 by vpacheco          #+#    #+#             */
/*   Updated: 2023/09/12 13:13:08 by paulorod         ###   ########.fr       */
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
	i = 0;
	while (env[i])
	{
		array[i] = ft_strdup(env[i]);
		i++;
	}
	return (array);
}

/*Free command struct*/
void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*temp;

	while (cmd)
	{
		i = 0;
		while (cmd->cmd[i])
		{
			free(cmd->cmd[i]);
			cmd->cmd[i] = NULL;
			i++;
		}
		if (cmd->path)
			free(cmd->path);
		if (cmd->redirs)
		{
			free(cmd->redirs->redirection);
			free(cmd->redirs);
		}
		free(cmd->cmd);
		temp = cmd->next;
		free(cmd);
		cmd = temp;
	}
}

/*Custom getenv fucntion that searches our environment variable list*/
char	*ft_getenv(const char *name, char ***_env)
{
	int		i;
	char	*value;
	char	**env;

	i = 0;
	env = *_env;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			value = ft_strchr(env[i], '=');
			return (value + 1);
		}
		i++;
	}
	return (NULL);
}
