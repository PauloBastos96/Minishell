/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:55:29 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/26 13:31:24 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Output redirection*/
void	handle_redir_out(t_shell *shell)
{
	int	fd;

	fd = open(shell->cmd->redirs->redirection, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (fd == -1)
	{
		perror(NULL);
		free_all(shell);
		exit(127);
	}
	swap_fd(&shell->cmd->std.out, fd);
}

/*Input redirection*/
void	handle_redir_in(t_shell *shell)
{
	int	fd;

	fd = open(shell->cmd->redirs->redirection, O_RDONLY);
	if (fd == -1)
	{
		perror(NULL);
		free_all(shell);
		exit(127);
	}
	swap_fd(&shell->cmd->std.in, fd);
}

/*Output redirection in append mode*/
void	handle_redir_out_append(t_shell *shell)
{
	int	fd;

	fd = open(shell->cmd->redirs->redirection, O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (fd == -1)
	{
		perror(NULL);
		free_all(shell);
		exit(127);
	}
	swap_fd(&shell->cmd->std.out, fd);
}

/*Get env variable*/
char	*get_var(char *str)
{
	int		i;
	char	*var;

	i = 1;
	while (var_char_valid(str[i]))
		i++;
	var = ft_substr(str, 0, i);
	return (var);
}
