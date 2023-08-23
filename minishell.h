/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:38 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/23 13:19:29 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "
# define _GNU_SOURCE

# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "Libft/libft.h"
# include "includes/list.h"
# include "includes/builtins.h"

extern bool	g_using_sub_process;
t_list	**new_env_list(char **env);
void	clear_env_list(t_list **env_list);
void	register_signals(void);
void	free_cmd(t_cmd *cmd);
int		print_fd(char *error, char fd, char *name);
int		create_command_process(t_cmd *cmd, char **env);
char	**alloc_cmd(char *command);
char	**fill_envs(const char **env);
char	*search_command_path(char *command);
char	**create_cmd(char *command);

#endif
