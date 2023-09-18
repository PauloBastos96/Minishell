/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:58:53 by vpacheco          #+#    #+#             */
/*   Updated: 2023/09/18 14:50:55 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "list.h"
# include "shell.h"
# include "../minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

bool	is_exit_code_valid(char	*str);
bool	is_expression_valid(char **cmd);
bool	is_duplicate(char **env, char *new);
char	*get_home_path(char *path);
char	**sort_envs(char **envs);
char	*add_quotes(char *str);
int		ft_echo(t_shell *shell);
int		ft_pwd(t_shell *shell);
int		ft_cd(t_shell *shell);
int		ft_env(t_shell *shell);
int		ft_export(t_shell *shell);
int		ft_unset(t_shell *shell);
int		ft_exit(t_shell *shell);

#endif
