/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpacheco <vpacheco@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:38 by paulorod          #+#    #+#             */
/*   Updated: 2023/08/02 17:59:45 by vpacheco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "

# include "Libft/libft.h"
#include "includes/list.h"
# include <readline/readline.h>
# include <readline/history.h>

void	ft_echo(t_cmd *cmd, int output);
void	ft_pwd(int output);
void	ft_cd(t_cmd *cmd, char **env);
void	ft_env(t_cmd *cmd, char **env, int output);
void	ft_clear(void);
int		print_fd(char *error, char fd, char *name);

#endif
