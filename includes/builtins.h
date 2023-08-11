/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:58:53 by vpacheco          #+#    #+#             */
/*   Updated: 2023/08/11 16:05:10 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "list.h"
# include "../minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

char	*get_home_path(char *path);
bool	is_exit_code_valid(char	*str);
char	**sort_envs(char **envs);
int		ft_echo(t_cmd *cmd, int output);
int		ft_pwd(t_cmd *cmd, int output);
int		ft_cd(t_cmd *cmd);
int		ft_env(t_cmd *cmd, const char **env, int output);
int		ft_export(t_cmd *cmd, const char **env);
int		ft_exit(t_cmd *cmd);

#endif
