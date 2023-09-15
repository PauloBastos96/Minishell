/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:10:51 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/15 16:07:41 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char* expand_env_var(t_shell *shell,char *var)
{
	return(ft_getenv(var, &shell->env));
}

char* str_replace(char* string, const char* substr, const char* replacement) {
	char* tok = NULL;
	char* newstr = NULL;
	char* oldstr = NULL;
	int   oldstr_len = 0;
	int   substr_len = 0;
	int   replacement_len = 0;

	newstr = ft_strdup(string);
	substr_len = ft_strlen(substr);
	replacement_len = ft_strlen(replacement);
	if (substr == NULL || replacement == NULL) {
		return newstr;
	}
	while ((tok = ft_strnstr(newstr, substr, ft_strlen(newstr)))) {
		oldstr = newstr;
		oldstr_len = ft_strlen(oldstr);
		newstr = (char*)malloc(sizeof(char) * (oldstr_len - substr_len + replacement_len + 1));
		if (newstr == NULL) {
			free(oldstr);
			return NULL;
		}
		ft_memcpy(newstr, oldstr, tok - oldstr);
		ft_memcpy(newstr + (tok - oldstr), replacement, replacement_len);
		ft_memcpy(newstr + (tok - oldstr) + replacement_len, tok + substr_len, oldstr_len - substr_len - (tok - oldstr));
		ft_memset(newstr + oldstr_len - substr_len + replacement_len, 0, 1);
		free(oldstr);
	}
	free(string);
	return newstr;
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
		definer = str_replace(definer, "$PWD", expanded_var);
		write(h_doc[1], definer, ft_strlen(definer));
		write(h_doc[1], "\n", 1);
	}
	close_safe(&h_doc[1]);
}
