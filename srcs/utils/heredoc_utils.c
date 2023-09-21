/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:11:27 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/21 16:38:21 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*str_replace(char *string, char *substr, char *replacement)
{
	char	*substr_src;
	char	*new_str;
	int		str_len;

	str_len = ft_strlen(string) - ft_strlen(substr) + ft_strlen(replacement);
	new_str = (char *)ft_calloc(sizeof(char), str_len + 1);
	if (!new_str)
		return (NULL);
	substr_src = ft_strnstr(string, substr, ft_strlen(string));
	ft_strlcpy(new_str, string, substr_src - string + 1);
	ft_strlcat(new_str, replacement, str_len + 1);
	ft_strlcat(new_str, substr_src + ft_strlen(substr), str_len + 1);
	free(string);
	return(new_str);
}

bool	var_char_valid(char c)
{
	return (!(c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
			|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
			|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
			|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
			|| c == '~' || c == '"' || c == '`' || c == '(' || c == ')'
			|| c == '$' || c == '\1' || c == '\0' || c == '=' || c == '-'
			|| c == '&' || c == '*'));
}

bool	to_expand(char *limiter)
{
	if (limiter[0] == '"' && limiter[ft_strlen(limiter) - 1] == '"')
		return (false);
	else
		return (true);
}