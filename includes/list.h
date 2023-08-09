/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:54:57 by vpacheco          #+#    #+#             */
/*   Updated: 2023/08/08 16:24:57 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../Libft/libft.h"

typedef struct s_cmd	t_cmd;

//comand list
struct s_cmd
{
	int		output;
	int		input;
	char	*path;
	char	**cmd;
	t_cmd	*next;
};

#endif
