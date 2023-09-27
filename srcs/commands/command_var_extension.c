/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_var_extension.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:14:29 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/26 15:46:23 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/shell.h"
#include "../../minishell.h"

/*Replace variable in token with its value*/
char	*replace_token_with_var(t_var_ext *var_ext, t_shell *shell)
{
	char	*var_value;
	char	*tmp;

	var_value = get_env_var(var_ext->token, shell, &var_ext->i, &var_ext->j);
	var_ext->n_tkn = join_values(var_ext->n_tkn, var_value);
	tmp = ft_strjoin(var_ext->n_tkn, &var_ext->token[var_ext->i]);
	free(var_ext->n_tkn);
	var_ext->n_tkn = extend_env_vars(tmp, shell, true);
	return (var_ext->n_tkn);
}

/*Expand exit code variable*/
char	*handle_exit_code_var(t_var_ext *var_ext, t_shell *shell)
{
	char	*tmp;
	char	*status;

	var_ext->n_tkn = replace_string(var_ext->n_tkn, ft_strdup(var_ext->token));
	while (ft_strnstr(var_ext->n_tkn, "$?", ft_strlen(var_ext->n_tkn)))
	{
		status = ft_itoa(shell->status);
		tmp = str_replace(ft_strdup(var_ext->n_tkn), 
				"$?", status);
		free(status);
		var_ext->n_tkn = replace_string(var_ext->n_tkn, tmp);
	}
	return (var_ext->n_tkn);
}

/*Check for quotes and copy start of token until it finds a var*/
void	var_pre_processing(t_var_ext *var_ext, bool *ignore_quotes)
{
	if (var_ext->token[var_ext->i] == '"')
		*ignore_quotes = !(*ignore_quotes);
	if (!(*ignore_quotes) && var_ext->token[var_ext->i] == '\'')
		var_ext->quote = !var_ext->quote;
	if (var_ext->token[var_ext->i] != '$')
		var_ext->n_tkn[var_ext->j] = var_ext->token[var_ext->i];
}

/*Set n_tkn value*/
char	*assign_n_tkn(t_var_ext *var_ext, t_shell *shell, int type)
{
	if (type == 0)
	{
		free(var_ext->n_tkn);
		var_ext->n_tkn = ft_strdup(var_ext->token);
	}
	else if (type == 1)
		var_ext->n_tkn = replace_token_with_var(var_ext, shell);
	else
		var_ext->n_tkn = handle_exit_code_var(var_ext, shell);
	return (var_ext->n_tkn);
}

/*Process env vars in tokens*/
char	*process_vars(t_var_ext *var_ext, bool *ignore_quotes, t_shell *shell)
{
	var_ext->i = -1;
	var_ext->j = 0;
	var_ext->quote = false;
	while (var_ext->token[++var_ext->i])
	{
		var_pre_processing(var_ext, ignore_quotes);
		if (var_ext->token[var_ext->i] == '$' && !var_ext->quote)
		{
			if (!var_char_valid(var_ext->token[var_ext->i + 1]))
				return (assign_n_tkn(var_ext, shell, 0));
			if (var_ext->token[++var_ext->i] != '?')
				return (assign_n_tkn(var_ext, shell, 1));
			else
				return (assign_n_tkn(var_ext, shell, 2));
		}
		else if (var_ext->quote)
			var_ext->n_tkn[var_ext->j] = var_ext->token[var_ext->i];
		var_ext->j++;
	}
	return (var_ext->n_tkn);
}
