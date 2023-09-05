/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:10:51 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/08/31 14:15:32 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	here_doc(char *command)
{
	char	**cmd;
	char	*buf;
	int		fd[2];

	if (pipe(fd) < -1)
		return (-1);
	//char	*limiter;
	cmd = ft_split(command, ' ');
	while (1)
	{
		buf = readline("heredoc>");
		//tmp = get_next_line(buf);
		if (ft_strcmp(cmd[2], buf) == 0)
			break ;
		//tmp = ft_strjoin(tmp, buf);
		write(fd[1], buf, ft_strlen(buf));
		free(buf);
	}
	return (fd[0]);
}

// heredoc_fd -> dup2(heredoc_fd, STDIN_FILENO)
