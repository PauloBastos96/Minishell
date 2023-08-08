/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:58:53 by vpacheco          #+#    #+#             */
/*   Updated: 2023/08/08 16:23:34 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "list.h"
# include "../minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

char	*get_home_path(char *path);
int		ft_echo(t_cmd *cmd, int output);
int		ft_pwd(int output);
int		ft_cd(t_cmd *cmd);
int		ft_env(t_cmd *cmd, char **env, int output);
void	ft_clear(void);

#endif
