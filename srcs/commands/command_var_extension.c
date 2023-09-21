/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_var_extension.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:14:29 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/21 14:26:08 by paulorod         ###   ########.fr       */
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
	var_ext->new_token = join_values(var_ext->new_token, var_value);
	tmp = ft_strjoin(var_ext->new_token, &var_ext->token[var_ext->i]);
	free(var_ext->new_token);
	var_ext->new_token = extend_env_vars(tmp, shell, true);
	return (var_ext->new_token);
}

/*Expand exit code variable*/
char	*handle_exit_code_var(char *new_token, t_shell *shell, int *j)
{
	new_token = join_values(new_token, ft_itoa(shell->status));
	while (new_token[*j])
		*j += 1;
	return (new_token);
}

/*Check for quotes and copy start of token until it finds a var*/
void	var_pre_processing(t_var_ext *var_ext, bool *ignore_quotes)
{
	if (var_ext->token[var_ext->i] == '"')
		*ignore_quotes = !(*ignore_quotes);
	if (!(*ignore_quotes) && var_ext->token[var_ext->i] == '\'')
		var_ext->quote = !var_ext->quote;
	if (var_ext->token[var_ext->i] != '$')
		var_ext->new_token[var_ext->j] = var_ext->token[var_ext->i];
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
			if (var_ext->token[++var_ext->i] != '?')
			{
				var_ext->new_token = replace_token_with_var(var_ext, shell);
				break ;
			}
			else
			{
				var_ext->new_token = handle_exit_code_var(var_ext->new_token,
						shell, &var_ext->j);
				break ;
			}
		}
		else if (var_ext->quote)
			var_ext->new_token[var_ext->j] = var_ext->token[var_ext->i];
		var_ext->j++;
	}
	return (var_ext->new_token);
}
