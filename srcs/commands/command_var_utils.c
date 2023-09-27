/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:53:26 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/27 14:47:25 by paulorod         ###   ########.fr       */
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

	if (key)
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
	free(var_name);
	if (!var_value)
	{
		while (token[*i] && (ft_isalnum(token[*i]) || token[*i] == '_'))
			*i += 1;
		var_value = ft_strdup("");
	}
	return (var_value);
}

/*Free split array*/
void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
