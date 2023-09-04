/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:16:56 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/04 12:31:54 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/commands.h"
#include "../../minishell.h"

/*Create sub-process for command*/
int	create_command_process(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		status;

	g_using_sub_process = true;
	pid = fork();
	status = 0;
	if (pid == 0)
	{
		if (execve(cmd->path, cmd->cmd, env) == -1)
			perror(NULL);
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_using_sub_process = false;
	}
	return (WEXITSTATUS(status));
}

/*Replace environment variables with their value*/
char	*handle_envs(char *token, t_shell *shell)
{
	char	*env_value;

	env_value = extend_env_vars(token, shell, false);
	if (env_value && *env_value)
	{
		free(token);
		return (env_value);
	}
	else if (env_value)
		free(env_value);
	return ("");
}

/* OLD CODE
Create command struct
char	**old_create_cmd(char *_cmd, t_shell *shell)
{
	char			**cmd;
	int				pos;
	size_t			i;
	unsigned int	j;

	cmd = alloc_cmd(_cmd);
	i = 0;
	j = 0;
	pos = 0;
	while (_cmd[i])
	{
		if (_cmd[i] == ' ')
		{
			cmd[pos] = handle_envs(ft_substr(_cmd, j, i - j), shell);
			pos++;
			j = i + 1;
		}
		else if (!_cmd[i + 1])
		{
			cmd[pos] = handle_envs(ft_substr(_cmd, j, i + 1 - j), shell);
			j = i + 1;
		}
		i++;
	}
	return (cmd);
}*/

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
	return (_command);
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

	i = 0;
	j = 0;
	command = ft_calloc(sizeof(t_cmd), 1);
	command->cmd = ft_calloc(sizeof(char *), 1);
	while (tokens[i])
	{
		if (!is_special_char(tokens[i], 0, NULL))
		{
			command->indentifier = _command;
			command->cmd[j++] = ft_strdup(tokens[i]);
		}
		else
		{
			j = 0;
			command->next = create_token_cmd(tokens[i]);
			command->next->next = create_cmd_list(&tokens[i + 1], shell);
			command = command->next;
			command->cmd = ft_calloc(sizeof(char *), 1);
		}
		i++;
	}
	command->cmd[j] = NULL;
	return (command);
}
