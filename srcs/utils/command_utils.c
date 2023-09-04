/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:32:32 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/01 15:43:12 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../minishell.h"

/*Get the value of the env variable*/
char	*get_var_value(char *key, t_shell *shell, int *i, int *j)
{
	char	*value;

	if (ft_strlen(key) > 1)
	{
		value = ft_getenv(key, &shell->env);
		if (value)
		{
			*i += ft_strlen(key);
			*j += ft_strlen(value);
			free(key);
			return (ft_strdup(value));
		}
		free(key);
		*i += ft_strlen(key);
	}
	return (NULL);
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

/*Get name of the env variable*/
char	*get_var_name(char *token)
{
	int		i;
	char	*name;

	i = 0;
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
		i++;
	name = ft_substr(token, 0, i);
	return (name);
}

/*Replace environment variables with their value*/
char	*extend_env_vars(char *token, t_shell *shell, bool ignore_quotes)
{
	int		i;
	int		j;
	bool	quote;
	char	*new_token;
	char	*var_name;
	char	*var_value;

	i = 0;
	j = 0;
	new_token = ft_calloc(sizeof(char), ft_strlen(token));
	quote = false;
	token = ft_strtrim(token, "\"");
	if (ft_strchr(token, '$'))
	{
		while (token[i])
		{
			if (!ignore_quotes)
			{
				if (token[i] == '\'')
					quote = !quote;
			}
			if (token[i] != '$')
				new_token[j] = token[i];
			else if (token[i] == '$' && !quote)
			{
				i++;
				if (token[i] != '?')
				{
					var_name = get_var_name(&token[i]);
					var_value = get_var_value(var_name, shell, &i, &j);
					if (!var_value)
					{
						while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
							i++;
						var_value = ft_strdup("");
					}
					new_token = join_values(new_token, var_value);
					if (new_token)
						new_token = extend_env_vars(ft_strjoin(new_token, &token[i]), shell, true);
					break ;
				}
				else
				{
					new_token = ft_strjoin(new_token, ft_itoa(shell->status));
					while (new_token[j])
						j++;
				}
			}
			else if (quote)
				new_token[j] = token[i];
			j++;
			i++;
		}
		return (new_token);
	}
	return (token);
}

/*Check if position "i" in string is a special character*/
bool	is_special_char(char *str, int i, int *end)
{
	if (str[i] == '|')
		return (true);
	if (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')
		return (true);
	if (str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>')
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
