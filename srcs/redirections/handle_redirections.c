/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:55:29 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/11 14:23:20 by ffilipe-         ###   ########.fr       */
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

void	handle_redir_hdoc(t_cmd *cmd)
{
	char *definer;
	int  h_doc[2];
	if(pipe(h_doc) == -1)
		exit(1); 
	swap_fd(&cmd->std.in, h_doc[0]);
	while(1)
	{
		definer = readline("heredoc> ");
		if (!definer)
		{
			
			print_fd("warning: here-document delimited by end-of-file (wanted `EOF')", STDERR_FILENO, "minishell");
			break ;
		}
		if(ft_strcmp(definer, cmd->redirs->redirection) == 0)
			break ;
		write(h_doc[1], definer, ft_strlen(definer));
		write(h_doc[1], "\n", 1);
	}
	close_safe(&h_doc[1]);

}

void	handle_redir_out_append(t_cmd *cmd)
{	
	int	fd;

	fd = open(cmd->redirs->redirection, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(NULL);
		return ;
	}
	swap_fd(&cmd->std.out, fd);
}
