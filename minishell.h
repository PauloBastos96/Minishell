/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:38 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/29 11:50:54 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "
# define _GNU_SOURCE

# include "Libft/libft.h"
# include "includes/builtins.h"
# include "includes/list.h"
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

extern bool	g_using_sub_process;
t_list		**new_env_list(char **env);
void		clear_env_list(t_list **env_list);
void		register_signals(void);
void		free_cmd(t_cmd *cmd);
int			print_fd(char *error, char fd, char *name);
int			create_command_process(t_cmd *cmd, char **env);
char		**create_cmd(char *command);
char		**alloc_cmd(char *command);
char		**fill_envs(const char **env);
char		*search_command_path(char *command);
void		handle_pipe_cmds(t_cmd **cmd, char *command, char **env);
int			check_pipes(char *cmd_str);
int			check_valid_pipe(char *cmd_str);
void		command_parser(t_cmd **cmd_struct, char *cmd_line);
void		insert_end(t_cmd **head, char *cmd);
void		insert_front(t_cmd **head, char *cmd);
void		free_list(t_cmd *head);
int			start_exec(t_cmd **cmd_struct, char **env);
int			run_command(t_cmd *cmd, char **env);
#endif
