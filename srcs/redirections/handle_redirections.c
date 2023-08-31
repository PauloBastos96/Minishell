/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:55:29 by ffilipe-          #+#    #+#             */
/*   Updated: 2023/08/31 15:52:40 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../minishell.h"

// int	handle_redir_out(t_cmd *cmd, char *file, char **env)
// {
// 	int		pid;
// 	int		files;
// 	char	*buff;

// 	(void)env;
// 	pid = fork();
// 	if (pid == -1)
// 		return (1);
// 	files = open(file, O_RDONLY);
// 	dup2(files, STDIN_FILENO);
// 	close(files);
// 	while (1)
// 	{
// 		buff = get_next_line(files);
// 		if (!buff)
// 			break ;
// 		write(files, buff, ft_strlen(buff));
// 	}
// 	(void)run_command(cmd, env);
// 	return (0);
// }

// int	handle_redir_in(t_cmd *cmd, char *file, char **env)
// {
// 	int	pid;
// 	int	files;

// 	(void)env;
// 	pid = fork();
// 	if (pid == -1)
// 		return (1);
// 	files = open(file, O_WRONLY | O_CREAT, 0777);
// 	if (files == -1)
// 		return (1);
// 	dup2(files, STDOUT_FILENO);
// 	close(files);
// 	run_command(cmd, env);
// 	return (0);
// }

// void	handle_redir_in_hdoc(void)
// {
// 	printf("Redir In HDOC\n");
// }

// void	handle_redir_out_hdoc(void)
// {
// 	printf("Redir Out HDOC\n");
// }

// void	handle_redirs(t_cmd *cmd, char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd->cmd[2][i])
// 	{
// 		if (cmd->cmd[2][i] == '>')
// 		{
// 			if (cmd->cmd[2][i + 1] == '>')
// 			{
// 				handle_redir_in_hdoc();
// 				break ;
// 			}
// 			else
// 				handle_redir_in(cmd, "file", env);
// 		}
// 		else if (cmd->cmd[1][i] == '<')
// 		{
// 			if (cmd->cmd[1][i + 1] == '<')
// 			{
// 				handle_redir_out_hdoc();
// 				break ;
// 			}
// 			else
// 				handle_redir_out(cmd, "file", env);
// 		}
// 		i++;
// 	}
// }
