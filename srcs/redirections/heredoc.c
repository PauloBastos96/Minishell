/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:10:51 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/16 19:06:35 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*str_replace(char *string, const char *substr, const char *replacement)
{
	char	*tok;
	char	*newstr;
	char	*oldstr;
	int		oldstr_len;
	int		substr_len;
	int		replacement_len;

	tok = NULL;
	newstr = NULL;
	oldstr = NULL;
	oldstr_len = 0;
	substr_len = 0;
	replacement_len = 0;
	newstr = ft_strdup(string);
	substr_len = ft_strlen(substr);
	replacement_len = ft_strlen(replacement);
	if (substr == NULL || replacement == NULL)
		return (newstr);
	while ((tok = ft_strnstr(newstr, substr, ft_strlen(newstr))))
	{
		oldstr = newstr;
		oldstr_len = ft_strlen(oldstr);
		newstr = (char *)malloc(sizeof(char) * (oldstr_len - substr_len
				+ replacement_len + 1));
		if (newstr == NULL)
			return (free(oldstr), NULL);
		ft_memcpy(newstr, oldstr, tok - oldstr);
		ft_memcpy(newstr + (tok - oldstr), replacement, replacement_len);
		ft_memcpy(newstr + (tok - oldstr) + replacement_len, tok + substr_len,
			oldstr_len - substr_len - (tok - oldstr));
		ft_memset(newstr + oldstr_len - substr_len + replacement_len, 0, 1);
		free(oldstr);
	}
	return (free(string), newstr);
}

char	*get_var(char *str)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$')
	{
		while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
		{
			i++;
			j++;
		}
		var = ft_substr(str, i - j, j);
		return (var);
	}
	return (NULL);
}

char	*set_expansion(t_shell *shell, char *str)
{
	char	*var;
	char	*expanded_var;

	if (get_var(str))
	{
		var = get_var(str);
		if(ft_getenv(var + 1, &shell->env))
			expanded_var = ft_getenv(var + 1, &shell->env);
		str = str_replace(str, var, expanded_var);
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
		definer = set_expansion(shell, definer);
		write(h_doc[1], definer, ft_strlen(definer));
		write(h_doc[1], "\n", 1);
	}
	close_safe(&h_doc[1]);
}
