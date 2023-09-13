/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:55:29 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/13 12:41:58 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Output redirection*/
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

/*Input redirection*/
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

/*Get heredoc error message*/
char	*heredoc_error_message(char *redir)
{
	char	*tmp;
	char	*error;

	tmp = ft_strjoin(HEREDOC_ERROR, redir);
	error = ft_strjoin(tmp, "')");
	free(tmp);
	return (error);
}

/*Heredoc*/
void	handle_redir_hdoc(t_cmd *cmd)
{
	char	*definer;
	char	*error;
	int		h_doc[2];

	if (pipe(h_doc) == -1)
		exit(1);
	swap_fd(&cmd->std.in, h_doc[0]);
	error = heredoc_error_message(cmd->redirs->redirection);
	while (1)
	{
		definer = readline("heredoc> ");
		if (!definer)
		{
			print_fd(error, STDERR_FILENO, "minishell");
			free(error);
			break ;
		}
		if (ft_strcmp(definer, cmd->redirs->redirection) == 0)
			break ;
		write(h_doc[1], definer, ft_strlen(definer));
		write(h_doc[1], "\n", 1);
	}
	close_safe(&h_doc[1]);
}

/*Output redirection in append mode*/
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
