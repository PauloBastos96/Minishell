/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:30:32 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/25 17:16:18 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../minishell.h"

/*Search for command executable in PATH directories
	and return the full path*/
char	*get_full_path(char **paths, char *command)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], command);
		if (!access(full_path, F_OK))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

/*Get command executable path*/
char	*search_command_path(char *command, t_shell *shell)
{
	char	*path_var;
	char	**paths;
	char	*full_path;
	char	*cmd_path;

	path_var = ft_getenv("PATH", &shell->env);
	if (path_var && ft_strlen(command) > 0)
		paths = ft_split(path_var, ':');
	else
		return (print_fd("Command not found", 2, command), NULL);
	if (paths)
	{
		cmd_path = ft_strjoin("/", command);
		full_path = get_full_path(paths, cmd_path);
		if (!full_path)
			print_fd("Command not found", 2, command);
		free(cmd_path);
		clear_paths(paths);
		return (full_path);
	}
	return (NULL);
}

/*Clear paths variable*/
void	clear_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}
