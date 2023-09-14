/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:10:51 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/14 16:00:44 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char* expand_env_var(t_shell *shell,char *var)
{
	return(ft_getenv(var, &shell->env));
}

char str_replace(char *str)
{

}
/*Get heredoc error message*/
void	heredoc_error_message(char *redir)
{
	char	*tmp;
	char	*error;

	tmp = ft_strjoin(HEREDOC_ERROR, redir);
	error = ft_strjoin(tmp, "')");
	free(tmp);
	print_fd(error, STDERR_FILENO, "minishell");
	free(error);
}

/*Heredoc*/
void	handle_redir_hdoc(t_shell *shell)
{
	t_cmd	*cmd;
	char	*definer;
	char	*expanded_var;
	int		h_doc[2];

	cmd = shell->cmd;
	if (pipe(h_doc) == -1)
		exit(1);
	swap_fd(&cmd->std.in, h_doc[0]);
	while (1)
	{
		definer = readline("heredoc> ");
		if (!definer)
		{
			heredoc_error_message(cmd->redirs->redirection);
			break ;
		}
		if (ft_strcmp(definer, cmd->redirs->redirection) == 0)
			break ;
		if(to_expand(definer) == true)
			expanded_var = get_var(definer);
		
		write(h_doc[1], definer, ft_strlen(definer));
		write(h_doc[1], "\n", 1);
	}
	close_safe(&h_doc[1]);
}
