/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:16:56 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/26 13:56:14 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/shell.h"
#include "../../minishell.h"

/*Get command type indentifier*/
enum e_identifiers	get_cmd_type(char *token)
{
	if (ft_strlen(token) == 1)
	{
		if (*token == '|')
			return (_pipe);
		if (*token == '>')
			return (great);
		if (*token == '<')
			return (less);
	}
	else
	{
		if (*token == '>')
			return (append);
		if (*token == '<')
			return (h_doc);
	}
	return (single);
}

/*Create empty command struct for pipes and redirections*/
t_cmd	*create_token_cmd(char *token)
{
	t_cmd	*command;

	(void)token;
	command = ft_calloc(sizeof(t_cmd), 1);
	if (!command)
		return (NULL);
	command->indentifier = unknown;
	return (command);
}

/*Get alloc size for command array*/
int	get_cmd_size(char **tokens)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (tokens[i])
	{
		if (!is_special_char(tokens[i], 0, NULL))
			size++;
		else if (tokens[i][0] == '|')
			break ;
		else
			i++;
		i++;
	}
	return (size + 1);
}

int	create_cmds(char **tokens, t_cmd **command, int *j)
{
	int	i;
	int	check;

	i = 0;
	while (tokens[i])
	{
		(*command)->indentifier = (enum e_identifiers)get_cmd_type(tokens[i]);
		if (!is_special_char(tokens[i], 0, NULL))
			(*command)->cmd[(*j)++] = ft_strdup(tokens[i]);
		else
		{
			check = set_redirs(tokens, &i, *command);
			if (check == 1)
				continue ;
			else if (check == -1)
				return (1);
			*command = set_next_cmd(command, j, i, tokens);
		}
		i++;
	}
	return (0);
}

/*Create linked list of command structs*/
t_cmd	*create_cmd_list(char **tokens)
{
	int		j;
	t_cmd	*command;

	j = 0;
	command = ft_calloc(sizeof(t_cmd), 1);
	if (!command)
		return (NULL);
	command->std = (t_std){-1, -1};
	command->h_doc[0] = -1;
	command->h_doc[1] = -1;
	command->fd[0] = -1;
	command->fd[1] = -1;
	command->cmd = ft_calloc(sizeof(char *), get_cmd_size(tokens));
	if (!command->cmd)
		return (NULL);
	if (create_cmds(tokens, &command, &j))
		return (NULL);
	command->cmd[j] = NULL;
	while (command->prev)
		command = command->prev;
	return (command);
}
