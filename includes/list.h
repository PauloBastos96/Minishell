/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:54:57 by vpacheco          #+#    #+#             */
/*   Updated: 2023/09/05 13:02:40 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../Libft/libft.h"

typedef struct s_cmd	t_cmd;

enum	e_identifiers {_command, _pipe, input, output, heredoc, append};

//comand list
struct					s_cmd
{
	pid_t				pid;
	enum e_identifiers	indentifier;
	int					fd[2];
	int					dup_fd[2];
	char				*path;
	char				**cmd;
	t_cmd				*next;
	t_cmd				*prev;
};

#endif
