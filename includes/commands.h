/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:35:52 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/11 13:47:53 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "list.h"
# include "shell.h"

typedef struct s_var_ext
{
	char	*token;
	char	*new_token;
	int		i;
	int		j;
	bool	quote;
}			t_var_ext;

char	*join_values(char *v1, char *v2);
char	*extend_env_vars(char *token, t_shell *shell, bool ignore_quotes);
char	*get_env_var(char *token, t_shell *shell, int *i, int *j);
char	*process_vars(t_var_ext *var_ext, bool ignore_quotes, t_shell *shell);
char	*remove_quotes(char *token);
bool	is_special_char(char *str, int i, int *end);
bool	in_quotes(char c);

#endif
