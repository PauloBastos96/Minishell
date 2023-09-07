/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:32:32 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/07 15:50:25 by paulorod         ###   ########.fr       */
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

/*Replace environment variables with their value*/
char	*extend_env_vars(char *token, t_shell *shell, bool ignore_quotes)
{
	t_var_ext	var_ext;

	var_ext.token = ft_strtrim(token, "\"");
	free(token);
	if (ft_strchr(var_ext.token, '$'))
	{
		var_ext.new_token = ft_calloc(sizeof(char),
				ft_strlen(var_ext.token) + 1);
		var_ext.new_token = process_vars(&var_ext, ignore_quotes, shell);
		free(var_ext.token);
		return (var_ext.new_token);
	}
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
