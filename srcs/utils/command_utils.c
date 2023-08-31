/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:32:32 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/31 16:39:25 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../minishell.h"

/*Get the value of the env variable*/
char	*get_var_value(char *key, t_shell *shell)
{
	char	*value;

	if (ft_strlen(key) > 1)
	{
		value = ft_getenv(key, &shell->env);
		free(key);
		if (value)
			return (ft_strdup(value));
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

/*Parse command and extend env variables*/
char	*parse_command(char *command, t_shell *shell)
{
	int		i;
	int		j;
	int		start;
	char	*env_var;
	char	*env_value;
	char	*final_value;
	char	*temp;
	bool	quote;

	i = 0;
	j = 0;
	start = 0;
	env_value = ft_strdup("");
	final_value = ft_strdup("");
	quote = false;
	while (command[i])
	{
		//Increment lenght of the start of the string until it finds a variable
		start++;
		//Check if the variable is in quotes and should be ignored
		if (command[i] == '\'')
			quote = !quote;
		if (command[i] == '$' && !quote)
		{
			//Define start of the variable name
			j = i + 1;
			i++;
			//Find lenght of the variable name
			while (command[i] && (ft_isalnum(command[i]) || command[i] == '_'))
				i++;
			//Get the name of the variable
			env_var = ft_substr(command, j, i - j);
			//Get value of the variable
			temp = get_var_value(env_var, shell);
			//Join value of the variable into the rest
			if (temp)
				env_value = ft_strdup(temp);
			temp = malloc(sizeof(char) * start + 1);
			//Copy start of the command until it finds a variable
			ft_strlcpy(temp, command, start);
			//Add the start of the command, the value of the variable
			//and the rest of the command together
			if (env_value)
				final_value = ft_strjoin(final_value, env_value);
			else
				return (ft_strjoin(temp, &command[i]));
		}
		if (!command[i] || !ft_strchr(command, '$'))
			break ;
		i++;
	}
	return (final_value);
}

char	*get_var_name(char *token)
{
	int		i;
	char	name;

	i = 0;
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
		i++;
	name = ft_calloc(sizeof(char), i);
}

char	*extend_env_vars(char *token, t_shell *shell)
{
	int		i;
	bool	quote;
	char	*new_token;

	i = 0;
	new_token = ft_calloc(sizeof(char), ft_strlen(token));
	while (token[i])
	{
		if (token[i] == '\'')
			quote = !quote;
		if (token[i] != '$')
			new_token[i] = token[i];
		else if (token[i] == '$' && !quote)
		{
			while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
				i++;
		}
		i++;
	}
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
