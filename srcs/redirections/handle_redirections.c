/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:55:29 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/09/05 13:08:48 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_redir_out(t_cmd *cmd)
{
    (void)cmd;
    return(1);
}

int	handle_redir_in(t_cmd *cmd)
{
    (void)cmd;
    return(1);
}

void	handle_redir_in_hdoc(void)
{
	printf("Redir In HDOC\n");
}

void	handle_redir_out_hdoc(void)
{
	printf("Redir Out HDOC\n");
}
