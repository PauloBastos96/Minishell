/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:32:32 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/29 13:14:12 by paulorod         ###   ########.fr       */
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
