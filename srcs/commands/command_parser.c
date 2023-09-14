/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:18:12 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/14 12:43:07 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/commands.h"
#include "../../minishell.h"

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

/*Check for unclosed quotes*/
char	*check_unclosed_quotes(char *command)
{
	char	*rl_tmp;
	char	*promt;
	int		i;

	if (in_quotes(0))
	{
		if (!in_quotes('"'))
			promt = "dquote>";
		else if (!in_quotes('\''))
			promt = "quote>";
		rl_tmp = readline(promt);
		command = join_values(command, rl_tmp);
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

/*Split command into tokens*/
char	**create_cmd_tokens(char *command, t_shell *shell)
{
	char	**tokens;
	int		i;

	i = 0;
	command = prepare_string(command);
	command = separate_special_chars(command);
	tokens = ft_split(command, '\1');
	while (tokens[i])
	{
		tokens[i] = handle_envs(tokens[i], shell);
		i++;
	}
	free(command);
	return (tokens);
}