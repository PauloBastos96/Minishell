/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:10:51 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/21 16:31:20 by ffilipe-         ###   ########.fr       */
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
			printf("from: %s\n", str);
			str = str_replace(str, var, expanded_var);
			printf("to: %s\n", str);
			i += ft_strlen(expanded_var) - 1;
		}
		else
			str = str_replace(str, var, "");
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
	int		h_doc[2];

	cmd = shell->cmd;
	if (pipe(h_doc) == -1)
		exit(1);
	swap_fd(&cmd->std.in, h_doc[0]);
	if (to_expand(cmd->redirs->redirection) == true)
		cmd->redirs->to_expand = true;
	cmd->redirs->redirection = remove_quotes(cmd->redirs->redirection);
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
		if (cmd->redirs->to_expand == true)
			definer = set_expansion(shell, definer);
		write(h_doc[1], definer, ft_strlen(definer));
		write(h_doc[1], "\n", 1);
	}
	close_safe(&h_doc[1]);
}
