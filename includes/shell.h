/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:55:45 by vpacheco          #+#    #+#             */
/*   Updated: 2023/08/28 12:45:01 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "list.h"

typedef struct s_shell	t_shell;

//Shell data struct
struct s_shell
{
	char		**env;
	int			status;
	t_cmd		*cmd;
};

#endif
