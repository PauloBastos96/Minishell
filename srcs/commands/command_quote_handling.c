/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_quote_handling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:31:05 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/12 15:58:54 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/shell.h"
#include "../../minishell.h"

/*Check if character is between quotes*/
bool	in_quotes(char c)
{
	static bool	d_quote = false;
	static bool	s_quote = false;

	if (c == '"' && !s_quote)
		d_quote = !d_quote;
	if (c == '\'' && !d_quote)
		s_quote = !s_quote;
	return (d_quote || s_quote);
}

/*Get number of quotes to ignore in token*/
int	get_quote_count(char *token)
{
	int		i;
	int		quotes;
	bool	in_quote;
	bool	in_dquote;

	i = 0;
	quotes = 0;
	in_quote = false;
	in_dquote = false;
	while (token[i])
	{
		if (token[i] == '"' && !in_quote)
		{
			in_dquote = !in_dquote;
			quotes++;
		}
		if (token[i] == '\'' && !in_dquote)
		{
			in_quote = !in_quote;
			quotes++;
		}
		i++;
	}
	return (quotes);
}

/*Copy token to new variable without the quotes*/
char	*quote_removal(char	*token, char *new, bool in_dquote, bool in_quote)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '"' && !in_quote)
			in_dquote = !in_dquote;
		if (token[i] == '\'' && !in_dquote)
			in_quote = !in_quote;
		if ((token[i] == '"' && in_quote) || (token[i] == '\'' && in_dquote))
		{
			new[j] = token[i];
			j++;
		}
		else if (token[i] != '"' && token[i] != '\'')
		{
			new[j] = token[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

/*Remove quotes from token*/
char	*remove_quotes(char *token)
{
	char	*new;
	bool	in_quote;
	bool	in_dquote;

	in_quote = false;
	in_dquote = false;
	new = ft_calloc(sizeof(char),
			ft_strlen(token) - get_quote_count(token) + 1);
	new = quote_removal(token, new, in_dquote, in_quote);
	return (new);
}
