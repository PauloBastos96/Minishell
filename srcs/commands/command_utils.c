/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:32:32 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/11 14:43:12 by paulorod         ###   ########.fr       */
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

/*Join multiple strings and free old ones*/
char	*join_values(char *v1, char *v2)
{
	char	*value;

	if (!v1 || !v2)
	{
		if (v1)
			free(v1);
		if (v2)
			free(v2);
		return (NULL);
	}
	value = ft_strjoin(v1, v2);
	free(v1);
	free(v2);
	return (value);
}

/*Check if position "i" in string is a special character*/
bool	is_special_char(char *str, int i, int *end)
{
	if (str[i] == '|')
		return (true);
	if (str[i] == '<' && str[i + 1] != '<' && (i == 0 || str[i - 1] != '<'))
		return (true);
	if (str[i] == '>' && str[i + 1] != '>' && (i == 0 || str[i - 1] != '>'))
		return (true);
	if (str[i] == '<' && str[i + 1] == '<')
	{
		if (end)
			*end = i + 1;
		return (true);
	}
	if (str[i] == '>' && str[i + 1] == '>')
	{
		if (end)
			*end = i + 1;
		return (true);
	}
	return (false);
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

/*Remove quotes from token*/
char	*remove_quotes(char *token)
{
	char	*new;
	bool	in_quote;
	bool	in_dquote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	in_quote = false;
	in_dquote = false;
	new = ft_calloc(sizeof(char),
			ft_strlen(token) - get_quote_count(token) + 1);
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

/*Replace environment variables with their value*/
char	*extend_env_vars(char *token, t_shell *shell, bool ignore_quotes)
{
	t_var_ext	var_ext;
	char		*tmp;

	var_ext.token = token;
	if (ft_strchr(var_ext.token, '$'))
	{
		var_ext.new_token = ft_calloc(sizeof(char),
				ft_strlen(var_ext.token) + 1);
		var_ext.new_token = process_vars(&var_ext, ignore_quotes, shell);
		free(var_ext.token);
		tmp = remove_quotes(var_ext.new_token);
		free(var_ext.new_token);
		var_ext.new_token = tmp;
		return (var_ext.new_token);
	}
	tmp = remove_quotes(var_ext.token);
	free(var_ext.token);
	var_ext.token = tmp;
	return (var_ext.token);
}

/*Replace environment variables with their value*/
char	*handle_envs(char *token, t_shell *shell)
{
	char	*env_value;

	env_value = extend_env_vars(token, shell, false);
	if (env_value && *env_value)
		return (env_value);
	else if (env_value)
		free(env_value);
	return (ft_strdup(""));
}
