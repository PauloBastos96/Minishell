/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:32:32 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/26 13:55:29 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../minishell.h"

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

/*Check for unclosed quotes*/
bool	has_unclosed_quotes(char *str)
{
	int		i;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	s_quote = false;
	d_quote = false;
	while (str[i])
	{
		if (str[i] == '"' && !s_quote)
			d_quote = !d_quote;
		if (str[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		i++;
	}
	return (s_quote || d_quote);
}

/*Replace environment variables with their value*/
char	*extend_env_vars(char *token, t_shell *shell, bool ignore_quotes)
{
	t_var_ext	ext;

	if (!token)
		return (NULL);
	ext.token = ft_strdup(token);
	free(token);
	if (has_unclosed_quotes(ext.token))
		return (unclosed_quotes_error(&ext));
	if (ft_strchr(ext.token, '$'))
	{
		ext.n_tkn = ft_calloc(sizeof(char),
				ft_strlen(ext.token) + 1);
		if (!ext.n_tkn)
			return (ext.token);
		ext.n_tkn = process_vars(&ext, &ignore_quotes, shell);
		free(ext.token);
		if (has_unclosed_quotes(ext.n_tkn))
			ext.n_tkn = replace_string(ext.n_tkn, remove_quotes(ext.n_tkn));
		else
			ext.n_tkn = replace_string(ext.n_tkn, ft_strdup(ext.n_tkn));
		return (ext.n_tkn);
	}
	return (ext.token);
}

/*Replace environment variables with their value*/
char	*pre_extend_env_vars(char *token, t_shell *shell, bool ignore_quotes)
{
	t_var_ext	var_ext;

	if (!token)
		return (NULL);
	var_ext.token = ft_strdup(token);
	free(token);
	if (has_unclosed_quotes(var_ext.token))
		return (unclosed_quotes_error(&var_ext));
	if (ft_strchr(var_ext.token, '$'))
	{
		var_ext.n_tkn = ft_calloc(sizeof(char),
				ft_strlen(var_ext.token) + 1);
		if (!var_ext.n_tkn)
			return (var_ext.token);
		var_ext.n_tkn = process_vars(&var_ext, &ignore_quotes, shell);
		free(var_ext.token);
		return (var_ext.n_tkn);
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
