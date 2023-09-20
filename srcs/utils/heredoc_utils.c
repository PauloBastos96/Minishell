/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:11:27 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/20 14:18:04 by ffilipe-         ###   ########.fr       */
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

bool	var_char_valid(char c)
{
	return (!(c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
			|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
			|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
			|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
			|| c == '~' || c == '"' || c == '`' || c == '(' || c == ')'
			|| c == '$' || c == '\1' || c == '\0'
			|| c == '=' || c == '-' || c == '&' || c == '*'));
}

bool to_expand(char *limiter)
{
	if((limiter[0] == '"' && limiter[ft_strlen(limiter) - 1] == '"') || (limiter[0] == '\'' && limiter[ft_strlen(limiter) - 1] == '\''))
		return (false);
	else
		return (true);
}

t_cmd *set_quotes(t_cmd *cmd)
{
	t_redirs *tmp;
	int i;

	i = -1;
	while(cmd->cmd[++i])
		cmd->cmd[i] = remove_quotes(cmd->cmd[i]);
	tmp = cmd->redirs;
	while(cmd->redirs)
	{
		if(cmd->redirs->indentifier != h_doc)
			cmd->redirs->redirection = remove_quotes(cmd->redirs->redirection);
		cmd->redirs = cmd->redirs->next;		
	}
	cmd->redirs = tmp;
	return(cmd);
}