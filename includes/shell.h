/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:55:45 by vpacheco          #+#    #+#             */
/*   Updated: 2023/09/25 15:28:50 by ffilipe-         ###   ########.fr       */
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
	t_cmd		*start;
	t_cmd		*cmd;
};

#endif
