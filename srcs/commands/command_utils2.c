/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:47:42 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/22 14:56:27 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/shell.h"
#include "../../minishell.h"

/*Set the next command struct*/
t_cmd	*set_next_cmd(t_cmd **command, int *j, int i, char **tokens)
{
	t_cmd	*tmp_cmd;

	(*command)->next = create_token_cmd(tokens[i]);
	if ((*command)->next)
	{
		(*command)->cmd[*j] = NULL;
		tmp_cmd = *command;
		*command = (*command)->next;
		(*command)->prev = tmp_cmd;
		*j = 0;
		(*command)->cmd = ft_calloc(sizeof(char *),
				get_cmd_size(&tokens[i + 1]));
	}
	return (*command);
}

/*Display unclosed quotes error*/
void	*unclosed_quotes_error(t_var_ext *var_ext)
{
	print_fd("unclosed quotes", 2, "parsing error");
	free(var_ext->token);
	return (NULL);
}