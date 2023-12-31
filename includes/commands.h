/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:35:52 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/27 15:45:51 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "list.h"
# include "shell.h"

typedef struct s_var_ext
{
	char	*token;
	char	*n_tkn;
	int		i;
	int		j;
	bool	quote;
}			t_var_ext;

char	*join_values(char *v1, char *v2);
char	*extend_env_vars(char *token, t_shell *shell, bool ignore_quotes);
char	*pre_extend_env_vars(char *token, t_shell *shell, bool ignore_quotes);
char	*get_env_var(char *token, t_shell *shell, int *i, int *j);
char	*process_vars(t_var_ext *var_ext, bool *ignore_quotes, t_shell *shell);
char	*remove_quotes(char *token);
bool	is_special_char(char *str, int i, int *end);
bool	in_quotes(char c, bool *d_quote, bool *s_quote);
bool	has_unclosed_quotes(char *str);
int		get_quote_count(char *token);
int		get_cmd_size(char **tokens);
t_cmd	*set_next_cmd(t_cmd **command, int *j, int i, char **tokens);
t_cmd	*create_token_cmd(char *token);
void	*unclosed_quotes_error(t_var_ext *var_ext);
char	set_new_command(char *command, int i);

#endif
