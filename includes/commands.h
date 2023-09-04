/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:35:52 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/04 15:47:24 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "list.h"
# include "shell.h"

char	*join_values(char *v1, char *v2);
char	*extend_env_vars(char *token, t_shell *shell, bool ignore_quotes);
char	*get_env_var(char *token, t_shell *shell, int *i, int *j);
char	*process_vars(char *token, char *new_token,
			bool ignore_quotes, t_shell *shell);
bool	is_special_char(char *str, int i, int *end);
bool	in_quotes(char c);

#endif
