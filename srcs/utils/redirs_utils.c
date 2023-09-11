/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:38:53 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/11 15:19:39 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_redirs(char **tokens, int *i, t_shell *shell, t_cmd *command)
{
	t_redirs			*redirs;
	t_redirs			*tmp;
	enum e_identifiers	check;

	check = (enum e_identifiers)get_cmd_type(tokens[*i]);
	if (check == lesser || check == greater || check == output
		|| check == input)
	{
		redirs = ft_calloc(sizeof(t_redirs), 1);
		redirs->indentifier = check;
		redirs->redirection = handle_envs(tokens[++(*i)], shell);
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
