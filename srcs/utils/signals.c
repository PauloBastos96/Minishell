/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:15:57 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/25 15:24:33 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../minishell.h"

/*Handle SIGINT and SIGQUIT*/
static void	signal_handler(int signum)
{
	printf("\n");
	if (signum == SIGINT && !g_using_sub_process)
	{
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

void hdoc_sighandler(int sig)
{
	t_shell *s;
	s = shell();
	if(sig == SIGINT)
	{
		close(STDIN_FILENO);
		get_next_line(STDIN_FILENO);
		free_cmd(s->cmd);
	}
	exit(0);
}
