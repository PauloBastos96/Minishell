/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:54:57 by vpacheco          #+#    #+#             */
/*   Updated: 2023/09/04 12:15:58 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../Libft/libft.h"

typedef struct s_cmd	t_cmd;

enum	e_identifiers {_pipe, greater, lesser, output, input};

//comand list
struct					s_cmd
{
	pid_t				pid;
	enum e_identifiers	indentifier;
	int					fd[2];
	int					dup_fd[2];
	char				*path;
	char				**cmd;
	int					status;
	t_cmd				*next;
	t_cmd				*prev;
};

#endif
