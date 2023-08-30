/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:16:56 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/30 13:43:24 by paulorod         ###   ########.fr       */
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
	if (pid == 0)
	{
		if (execve(cmd->path, cmd->cmd, (char **)env) == -1)
			perror(NULL);
		exit(0);
	}
	else
	{
		wait(&status);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_using_sub_process = false;
	}
	return (status);
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

/*Create command struct*/
//TODO change to split by delimiter
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
}

/*Check if character is between quotes*/
bool	in_quotes(char c)
{
	static bool	d_quote = false;
	static bool	s_quote = false;

	if (c == '"' && !s_quote)
		d_quote = !d_quote;
	if (c == '\'' && !d_quote)
		s_quote = !s_quote;
	return (d_quote || s_quote);
}

/*Check for unclosed quotes*/
char	*check_unclosed_quotes(char *command)
{
	char	*rl_tmp;
	char	*tmp;
	char	*promt;
	int		i;

	if (in_quotes(0))
	{
		if (!in_quotes('"'))
			promt = "dquote>";
		else if (!in_quotes('\''))
			promt = "quote>";
		rl_tmp = readline(promt);
		tmp = ft_strjoin(command, rl_tmp);
		free(command);
		free(rl_tmp);
		command = tmp;
	}
	i = 0;
	while (command[i])
	{
		in_quotes(command[i]);
		i++;
	}
	if (in_quotes(0))
		command = check_unclosed_quotes(command);
	return (command);
}

/*Prepare string for token generation*/
char	*prepare_string(char *command)
{
	int		i;

	i = 0;
	while (command[++i])
	{
		if (in_quotes(command[i]))
			continue ;
		if (command[i] == ' ')
			command[i] = '\1';
	}
	command = check_unclosed_quotes(command);
	return (command);
}

/*Check if position "i" in string is a special character*/
bool	is_special_char(char *str, int i, int *end)
{
	if (str[i] == '|')
		return (true);
	if (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')
		return (true);
	if (str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>')
		return (true);
	if (str[i] == '<' && str[i + 1] == '<')
	{
		if (end)
			*end = i + 1;
		return (true);
	}
	if (str[i] == '>' && str[i + 1] == '>')
	{
		if (end)
			*end = i + 1;
		return (true);
	}
	return (false);
}

/*Copy old string and add separator between special characters*/
char	*add_separators(char *command, int start, int end)
{
	int		j;
	char	*new_command;

	new_command = ft_calloc(sizeof(char), ft_strlen(command) + 2);
	j = 0;
	while (command[j] && j < start)
	{
		new_command[j] = command[j];
		j++;
	}
	new_command[j++] = '\1';
	while (j <= end + 1)
	{
		new_command[j] = command[j - 1];
		j++;
	}
	new_command[j++] = '\1';
	while (command[j - 2])
	{
		new_command[j] = command[j - 2];
		j++;
	}
	new_command[j] = '\0';
	return (new_command);
}

/*Add separator (\1) between special characters*/
char	*separate_special_chars(char *command)
{
	int	i;
	int	end;

	i = 0;
	end = 0;
	while (command[i])
	{
		end = i;
		if (!in_quotes(command[i]) && is_special_char(command, i, &end))
		{
			if (command[i + 1] == '<' || command[i + 1] == '>')
			{
				if (command[i - 1] != '\1' || command[i + 2] != '\1')
					command = add_separators(command, i, end);
			}
			else
			{
				if (command[i - 1] != '\1' || command[i + 1] != '\1')
					command = add_separators(command, i, end);
			}
		}
		i++;
	}
	return (command);
}

t_cmd	*create_cmd_list(char **tokens)
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
			command->cmd[j++] = tokens[i];
		else
			command->next = create_cmd_list(&tokens[i + 1]);
		i++;
	}
	return (command);
}

/*Split command into tokens*/
char	**create_cmd_tokens(char *command, t_shell *shell)
{
	char	**cmd;

	(void)shell;
	command = prepare_string(command);
	command = separate_special_chars(command);
	cmd = ft_split(command, '\1');
	t_cmd *test = create_cmd_list(cmd);
	(void)test;
	return (cmd);
}

