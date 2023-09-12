/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:38:53 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/12 15:08:41 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_redirs(char **tokens, int *i, t_shell *shell, t_cmd *command)
{
	t_redirs			*redirs;
	t_redirs			*tmp;
	enum e_identifiers	check;

	(void)shell;
	check = (enum e_identifiers)get_cmd_type(tokens[*i]);
	if (check == lesser || check == greater || check == output
		|| check == input)
	{
		redirs = ft_calloc(sizeof(t_redirs), 1);
		redirs->indentifier = check;
		if (tokens[(*i) + 1])
			redirs->redirection = ft_strdup(tokens[++(*i)]);
		else
		{
			free(redirs);
			redirs = NULL;
			print_fd("parse error", 2, NULL);
		}
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
