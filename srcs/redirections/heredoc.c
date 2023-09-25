/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:10:51 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/25 15:53:06 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_var(char *str)
{
	int		i;
	char	*var;

	i = 1;
	while (var_char_valid(str[i]))
	{
		i++;
	}
	var = ft_substr(str, 0, i);
	return (var);
}

char	*set_expansion(t_shell *shell, char *str)
{
	char	*var;
	char	*expanded_var;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i++] != '$')
			continue ;
		if (!var_char_valid(str[i]))
			continue ;
		i--;
		var = get_var(str + i);
		if (!var)
			continue ;
		expanded_var = ft_getenv(var + 1, &shell->env);
		if (expanded_var)
		{
			str = str_replace(str, var, expanded_var);
			i += ft_strlen(expanded_var) - 1;
		}
		else
			str = str_replace(str, var, "");
		free(var);
	}
	return (str);
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

	cmd = shell->cmd;
	if (pipe(cmd->h_doc) == -1)
		exit(1);
	swap_fd(&cmd->std.in, cmd->h_doc[0]);
	if (to_expand(cmd->redirs->redirection) == true)
		cmd->redirs->to_expand = true;
	cmd->redirs->redirection = remove_quotes(cmd->redirs->redirection);
	while (1)
	{
		signal(SIGINT, hdoc_sighandler);
		write(STDIN_FILENO, "heredoc> ", 9);
		definer = get_next_line(STDIN_FILENO);
		if(ft_strrchr(definer, '\n'))
			definer[ft_strlen(definer) - 1] = '\0';
		if (!definer)
		{
			heredoc_error_message(cmd->redirs->redirection);
			break ;
		}
		if (ft_strcmp(definer, cmd->redirs->redirection) == 0)
			break ;
		if (cmd->redirs->to_expand == true)
			definer = set_expansion(shell, definer);
		write(cmd->h_doc[1], definer, ft_strlen(definer));
		write(cmd->h_doc[1], "\n", 1);
		free(definer);
	}
	signal(SIGINT, SIG_DFL);
	close_safe(&cmd->h_doc[1]);
}
