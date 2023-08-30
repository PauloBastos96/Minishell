/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:35:52 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/30 16:23:30 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "list.h"
# include "shell.h"

char	*get_var_value(char *key, t_shell *shell);
char	*join_values(char *v1, char *v2);
char	*parse_command(char *command, t_shell *shell);
bool	is_special_char(char *str, int i, int *end);
bool	in_quotes(char c);

#endif
