/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_var_extension.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:14:29 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/04 16:27:17 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/shell.h"
#include "../../minishell.h"

/*Get name of the env variable*/
static char	*get_var_name(char *token)
{
	int		i;
	char	*name;

	i = 0;
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
		i++;
	name = ft_substr(token, 0, i);
	return (name);
}

/*Get the value of the env variable*/
static char	*get_var_value(char *key, t_shell *shell, int *i, int *j)
{
	char	*value;

	if (ft_strlen(key) > 1)
	{
		value = ft_getenv(key, &shell->env);
		if (value)
		{
			*i += ft_strlen(key);
			*j += ft_strlen(value);
			return (ft_strdup(value));
		}
		*i += ft_strlen(key);
	}
	return (NULL);
}

/*Get environment variable*/
char	*get_env_var(char *token, t_shell *shell, int *i, int *j)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(&token[*i]);
	var_value = get_var_value(var_name, shell, i, j);
	if (!var_value)
	{
		while (token[*i] && (ft_isalnum(token[*i]) || token[*i] == '_'))
			*i += 1;
		var_value = ft_strdup("");
	}
	free(var_name);
	return (var_value);
}

/*Replace variable in token with its value*/
char	*replace_token_with_var(char *token, char *new_token,
	t_shell *shell, int *nbrs[2])
{
	char	*var_value;
	char	*tmp;

	var_value = get_env_var(token, shell, nbrs[0], nbrs[1]);
	new_token = join_values(new_token, var_value);
	tmp = ft_strjoin(new_token, &token[*nbrs[0]]);
	free(new_token);
	if (new_token)
		new_token = extend_env_vars(tmp, shell, true);
	return (new_token);
}

/*Expand exit code variable*/
char	*handle_exit_code_var(char *new_token, t_shell *shell, int *j)
{
	new_token = join_values(new_token, ft_itoa(shell->status));
	while (new_token[*j])
		*j += 1;
	return (new_token);
}

/*Process env vars in tokens*/
char	*process_vars(char *token, char *new_token,
	bool ignore_quotes, t_shell *shell)
{
	int		i;
	int		j;
	int		*nbrs[2];
	bool	quote;

	i = -1;
	j = 0;
	quote = false;
	while (token[++i])
	{
		if (!ignore_quotes && token[i] == '\'')
			quote = !quote;
		if (token[i] != '$')
			new_token[j] = token[i];
		else if (token[i] == '$' && !quote)
		{
			if (token[++i] != '?')
			{
				nbrs[0] = &i;
				nbrs[1] = &j;
				new_token = replace_token_with_var(token, new_token,
						shell, nbrs);
				break ;
			}
			else
				new_token = handle_exit_code_var(new_token, shell, &j);
		}
		else if (quote)
			new_token[j] = token[i];
		j++;
	}
	return (new_token);
}
