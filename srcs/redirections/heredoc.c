/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:10:51 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/13 10:46:50 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool to_expand(char *var)
{
	int i;

	i = 0;
	if(var[0] == '"' && var[ft_strlen(var) - 1] == '"')
		return (false);
	else
		return (true);
}

bool is_var(char *var)
{
	int i;

	i = 0;
	if(var[0] == '$')
		return (true);
	else
		return (false);
}
char *get_var(char *var)
{
	int i;

	i = 0;
	while(var[i])
	{
		if(var[i] == '$')
		{
			while(var[i] != ' ' && var[i] != '\0')
				i++;
			return(ft_substr(var, 0, i));
		}
		i++;
	}
	return(var);
}

void	handle_redir_hdoc(t_shell *shell)
{
	t_cmd *cmd;
	char *definer;
	char *expanded_var;
	int  h_doc[2];
	
	cmd = shell->cmd;
	if(pipe(h_doc) == -1)
		exit(1); 
	swap_fd(&cmd->std.in, h_doc[0]);
	while(1)
	{
		definer = readline("heredoc> ");
		if(to_expand(cmd->redirs->redirection) == true)
		{
			expanded_var = get_var(definer);
			if(is_var(expanded_var) == true)
				if(ft_getenv(expanded_var + 1, &shell->env) != NULL)
					definer = ft_getenv(expanded_var + 1, &shell->env);
		}
		if (!definer)
		{
			print_fd("warning: here-document delimited by end-of-file (wanted `EOF')", STDERR_FILENO, "minishell");
			break ;
		}
		if(ft_strcmp(definer, cmd->redirs->redirection) == 0)
			break ;
		write(h_doc[1], definer, ft_strlen(definer));
		write(h_doc[1], "\n", 1);
	}
	close_safe(&h_doc[1]);

}
