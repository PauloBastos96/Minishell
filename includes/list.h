/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:54:57 by vpacheco          #+#    #+#             */
/*   Updated: 2023/09/07 13:49:13 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../Libft/libft.h"

typedef struct s_cmd	t_cmd;
typedef struct s_redirs	t_redirs;
typedef struct s_std	t_std;

enum					e_identifiers
{
	unknown,
	_pipe,
	greater,
	lesser,
	output,
	input,
	single
};

struct					s_std
{
	int					in;
	int					out;
};

// comand list
struct					s_cmd
{
	pid_t				pid;
	enum e_identifiers	indentifier;
	int					fd[2];
	int					dup_fd[2];
	char				*path;
	char				**cmd;
	int					status;
	t_redirs			*redirs;
	t_std				std;
	t_cmd				*next;
	t_cmd				*prev;
};

struct					s_redirs
{
	char				*redirection;
	enum e_identifiers	indentifier;
	t_redirs			*next;
};

#endif
