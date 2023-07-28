/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:38 by paulorod          #+#    #+#             */
/*   Updated: 2023/07/28 14:44:03 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "minishell$ "

# include "Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

void	ft_echo(char *command);
void	ft_pwd(void);
void	ft_cd(char *path);
void	ft_clear(void);
void	ft_env(t_list **env_list);
t_list	**new_env_list(char **env);
void	clear_env_list(t_list **env_list);

#endif
