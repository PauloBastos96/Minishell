/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:38 by paulorod          #+#    #+#             */
/*   Updated: 2023/09/05 13:22:56 by ffilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "
# define _GNU_SOURCE

# include "Libft/libft.h"
# include "includes/builtins.h"
# include "includes/list.h"
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

extern bool	g_using_sub_process;
t_list		**new_env_list(char **env);
void		clear_env_list(t_list **env_list);
void		register_signals(void);
void		free_cmd(t_cmd *cmd);
void		clear_paths(char **paths);
int			print_fd(char *error, char fd, char *name);
int			create_command_process(t_cmd *cmd, char **env);
char		**alloc_cmd(char *command);
char		**fill_envs(const char **env);
char		*get_full_path(char **paths, char *command);
char		*search_command_path(char *command);
char		**create_cmd_tokens(char *command, t_shell *shell);
char		*ft_getenv(const char *name, char ***_env);
int	        exec_pipes(t_shell *shell);
t_cmd		*create_cmd_list(char **tokens, t_shell *shell);
char		**create_cmd_tokens(char *command, t_shell *shell);
int			run_command(t_shell *shell);
void        shell_loop(t_shell *shell);
int	        handle_redir_out(t_cmd *cmd);
t_cmd	    *command_parser(char *cmd_line, t_shell *shell);

#endif
