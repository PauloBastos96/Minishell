/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:38:53 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/14 10:50:19 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_redirs(char **tokens, int *i, t_shell *shell, t_cmd *command)
{
	t_redirs			*redirs;
	t_redirs			*tmp;
	enum e_identifiers	check;

	check = (enum e_identifiers)get_cmd_type(tokens[*i]);
	if (check == less || check == great || check == append
		|| check == h_doc)
	{
		redirs = ft_calloc(sizeof(t_redirs), 1);
		redirs->indentifier = check;
		if(tokens[++(*i)])
			redirs->redirection = handle_envs(tokens[++(*i)], shell);
		else
			return(print_fd("Parse error near `\\n'", STDERR_FILENO, "minishell"), -1);
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