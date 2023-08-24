/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 09:56:07 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/08/24 15:55:31 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_pipe_cmds(t_cmd **cmd, char *command, char **env)
{
	char	**cmd_args;
	int		i;

	i = 0;
	cmd = NULL;
	env = NULL;
	if (check_valid_pipe(command) == 1)
	{
		cmd_args = ft_split(command, '|');
		while (cmd_args[i])
		{
			command_parser(cmd, cmd_args[i]);
			i++;
		}
	}
	else
		print_fd("No such file or directory", 2, command);
	return ;
}

int	start_exec(t_cmd *cmd_struct, char **env)
{
	t_cmd	*tmp_cmd_s;

	env = NULL;
	tmp_cmd_s = cmd_struct;
	return (1);
}
