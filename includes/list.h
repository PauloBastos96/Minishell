/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpacheco <vpacheco@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:54:57 by vpacheco          #+#    #+#             */
/*   Updated: 2023/08/02 17:50:29 by vpacheco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "builtins.h"
# include "../Libft/libft.h"

typedef struct s_cmd t_cmd;

//comand list
struct s_cmd
{
	int		output;
	int		input;
	char	*path;
	char	**cmd;
	t_cmd 	*next;
};



#endif