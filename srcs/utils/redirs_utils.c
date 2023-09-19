/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:38:53 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/19 13:02:50 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Assign redirection*/
static t_redirs	*assign_redirs(t_redirs *redirs, char *token)
{
	if (token)
		redirs->redirection = ft_strdup(token);
	else
	{
		free(redirs);
		redirs = NULL;
		print_fd("parse error", 2, NULL);
	}
	return (redirs);
}

/*Set redirections struct data*/
int	set_redirs(char **tokens, int *i, t_cmd *command)
{
	t_redirs			*redirs;
	t_redirs			*tmp;
	enum e_identifiers	check;

	check = (enum e_identifiers)get_cmd_type(tokens[*i]);
	if (check >= great && check <= h_doc)
	{
		redirs = ft_calloc(sizeof(t_redirs), 1);
		redirs->indentifier = check;
		redirs = assign_redirs(redirs, tokens[++(*i)]);
		tmp = command->redirs;
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (!tmp)
			command->redirs = redirs;
		else
			tmp->next = redirs;
		(*i)++;
		return (1);
	}
	return (0);
}
