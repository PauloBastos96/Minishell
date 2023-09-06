/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:16:56 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/06 16:10:44 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/shell.h"
#include "../../minishell.h"

/*Create sub-process for command*/
int	create_command_process(t_cmd *cmd, char **env)
{
	int	status;

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (execve(cmd->path, cmd->cmd, env) == -1)
			perror("execve");
		//exit (127);
	}
	waitpid(cmd->pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

/*Get command type indentifier*/
enum e_identifiers	get_cmd_type(char *token)
{
	if (ft_strlen(token) == 1)
	{
		if (*token == '|')
			return (_pipe);
		if (*token == '>')
			return (output);
		if (*token == '<')
			return (input);
	}
	else
	{
		if (*token == '>')
			return (append);
		if (*token == '<')
			return (heredoc);
	}
	return (_pipe);
}

/*Create empty command struct for pipes and redirections*/
t_cmd	*create_token_cmd(char *token)
{
	t_cmd	*command;

	command = ft_calloc(sizeof(t_cmd), 1);
	command->fd[0] = STDIN_FILENO;
	command->fd[1] = STDOUT_FILENO;
	command->indentifier = (enum e_identifiers)get_cmd_type(token);
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
		else
			break ;
		i++;
	}
	return (size + 1);
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
	command->fd[0] = STDIN_FILENO;
	command->fd[1] = STDOUT_FILENO;
	command->cmd = ft_calloc(sizeof(char *), get_cmd_size(tokens));
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
	command->cmd[j] = NULL;
	while (command->prev)
		command = command->prev;
	return (command);
}
