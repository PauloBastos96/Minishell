/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:16:56 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/05 12:48:18 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/shell.h"
#include "../../minishell.h"

/*Create sub-process for command*/
int	create_command_process(t_cmd *cmd, char **env)
{
	int	i;

	i = 0;
	if (execve(cmd->path, cmd->cmd, (char **)env) == -1)
		perror("execve");
	return (0);
}

/*Replace environment variables with their value*/
static char	*handle_envs(char *command, t_shell *shell)
{
	char	*env_value;

	env_value = parse_command(command, shell);
	if (env_value && *env_value)
	{
		free(command);
		return (env_value);
	}
	else if (env_value)
		free(env_value);
	return (command);
}

/*Get command type indentifier*/
enum e_identifiers	get_cmd_type(char *token)
{
	if (ft_strlen(token) == 1)
	{
		if (*token == '|')
			return (_pipe);
		if (*token == '>')
			return (greater);
		if (*token == '<')
			return (lesser);
	}
	else
	{
		if (*token == '>')
			return (output);
		if (*token == '<')
			return (input);
	}
	return (_pipe);
}

/*Create empty command struct for pipes and redirections*/
t_cmd	*create_token_cmd(char *token)
{
	t_cmd	*command;

	command = ft_calloc(sizeof(t_cmd), 1);
	command->indentifier = (enum e_identifiers)get_cmd_type(token);
	return (command);
}

/*Create linked list of command structs*/
t_cmd	*create_cmd_list(char **tokens, t_shell *shell)
{
	int		i;
	int		j;
	t_cmd	*command;
	t_cmd	*tmp_cmd;

	i = 0;
	j = 0;
	command = ft_calloc(sizeof(t_cmd), 1);
	command->cmd = ft_calloc(sizeof(char *), 1);
	while (tokens[i])
	{
		if (!is_special_char(tokens[i], 0, NULL))
			command->cmd[j++] = handle_envs(tokens[i], shell);
		else
		{
			command->indentifier = (enum e_identifiers)get_cmd_type(tokens[i]);
			command->next = create_token_cmd(tokens[i]);
			if (command->next)
			{
				command->cmd[j] = NULL;
				tmp_cmd = command;
				command = command->next;
				command->prev = tmp_cmd;
				j = 0;
				command->cmd = ft_calloc(sizeof(char *), 1);
			}
		}
		i++;
	}
	while (command->prev)
		command = command->prev;
	return (command);
}
