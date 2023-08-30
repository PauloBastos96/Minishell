/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:32:32 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/30 16:22:00 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../minishell.h"

/*Get the value of the env variable*/
char	*get_var_value(char *key, t_shell *shell)
{
	char	*value;

	value = ft_getenv(key, &shell->env);
	free(key);
	if (value)
		return (ft_strdup(value));
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

/*Parse command and extend env variables*/
char	*parse_command(char *command, t_shell *shell)
{
	int		i;
	int		j;
	char	*env_var;
	char	*env_value;
	char	*temp;

	i = 0;
	j = 0;
	env_value = ft_strdup("");
	while (command[i])
	{
		if (command[i] == '$')
		{
			j = i + 1;
			while (command[i] && command[i] != ' ' && command[i + 1] != '$')
				i++;
			env_var = ft_substr(command, j, i - j);
			temp = get_var_value(env_var, shell);
			env_value = join_values(env_value, temp);
		}
		if (!command[i])
			break ;
		i++;
	}
	return (env_value);
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
