/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:15:57 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/10 15:43:06 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/shell.h"
#include "../../minishell.h"

/*Handle SIGINT and SIGQUIT*/
static void	signal_handler(int signum)
{
	if (signum == SIGINT && !g_using_sub_process)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*Register signals with signal handler*/
void	register_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
