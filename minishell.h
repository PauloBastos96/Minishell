/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:38 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/08 16:08:01 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "

# include "Libft/libft.h"
# include "includes/list.h"
# include <readline/readline.h>
# include <readline/history.h>

int		ft_echo(t_cmd *cmd, int output);
int		ft_pwd(int output);
int		ft_cd(t_cmd *cmd);
int		ft_env(t_cmd *cmd, char **env, int output);
void	ft_clear(void);
t_list	**new_env_list(char **env);
void	clear_env_list(t_list **env_list);
int		print_fd(char *error, char fd, char *name);
char	**alloc_cmd(char *command);

#endif
