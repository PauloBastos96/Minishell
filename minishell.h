/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:38 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/14 13:48:37 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "
# define HEREDOC_ERROR "warning: here-document delimited \
by end-of-file (wanted '"
# define _GNU_SOURCE

# include "Libft/libft.h"
# include "includes/builtins.h"
# include "includes/list.h"
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

extern bool			g_using_sub_process;
t_list				**new_env_list(char **env);
void				clear_env_list(t_list **env_list);
void				register_signals(void);
void				free_cmd(t_cmd *cmd);
void				clear_paths(char **paths);
int					print_fd(char *error, char fd, char *name);
int					create_command_process(t_cmd *cmd, char **env);
char				**alloc_cmd(char *command);
char				**fill_envs(const char **env);
char				*get_full_path(char **paths, char *command);
char				*search_command_path(char *command);
char				**create_cmd_tokens(char *command, t_shell *shell);
char				*ft_getenv(const char *name, char ***_env);
int					exec_pipes(t_shell *shell);
int					get_exit_code(char *cmd);
t_cmd				*create_cmd_list(char **tokens, t_shell *shell);
char				**create_cmd_tokens(char *command, t_shell *shell);
int					run_command(t_shell *shell);
void				shell_loop(t_shell *shell);
t_cmd				*command_parser(char *cmd_line, t_shell *shell);
void				handle_commands(t_shell *shell);
int					close_safe(int *fd);
int					set_redirs(char **tokens, int *i, t_cmd *command);
enum e_identifiers	get_cmd_type(char *token);
char				*handle_envs(char *command, t_shell *shell);
void				swap_fd(int *fd, int target);
void				handle_redir_out(t_shell *shell);
void				handle_redir_in(t_shell *shell);
void				handle_redir_hdoc(t_shell *shell);
void				handle_redir_out_append(t_shell *shell);
void				free_envs(t_shell *shell);
void				free_all(t_shell *shell);
#endif
