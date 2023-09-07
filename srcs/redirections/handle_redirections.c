/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:55:29 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/07 15:43:13 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_redir_out(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->redirs->redirection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(NULL);
		return (1);
	}
	swap_fd(&cmd->std.out, fd);
	return (1);
}

int	handle_redir_in(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->redirs->redirection, O_RDONLY);
	if (fd == -1)
	{
		perror(NULL);
		//ft_clean(cmd);
		exit(127);
	}
	swap_fd(&cmd->std.in, fd);
	return (1);
}

void	handle_redir_in_hdoc(void)
{
	printf("Redir In HDOC\n");
}

void	handle_redir_out_hdoc(void)
{
	printf("Redir Out HDOC\n");
}
