/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:58:53 by vpacheco          #+#    #+#             */
/*   Updated: 2023/08/24 13:59:56 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "list.h"
# include "../minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

bool	is_exit_code_valid(char	*str);
bool	is_duplicate(char **env, char *new);
char	*get_home_path(char *path);
char	**sort_envs(char **envs);
char	*add_quotes(char *str);
int		ft_echo(t_cmd *cmd, int output);
int		ft_pwd(t_cmd *cmd, int output);
int		ft_cd(t_cmd *cmd, char ***env);
int		ft_env(t_cmd *cmd, char **env, int output);
int		ft_export(t_cmd *cmd, char ***env);
int		ft_unset(char ***env, t_cmd *cmd);
int		ft_exit(t_cmd *cmd);
void	update_pwd(char ***_env);

#endif
