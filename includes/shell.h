/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpacheco <vpacheco@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:55:45 by vpacheco          #+#    #+#             */
/*   Updated: 2023/08/02 17:51:15 by vpacheco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "list.h"
# include "builtins.h"

typedef struct s_shell	t_shell;

//list for env
struct s_shell
{
	char		**env;
	int			status;
	t_cmd		*cmd;
};

#endif
