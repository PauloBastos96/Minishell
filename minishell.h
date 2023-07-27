/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:31:38 by paulorod          #+#    #+#             */
/*   Updated: 2023/07/27 15:53:32 by paulorod         ###   ########.fr       */
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
void	ft_env(char **env);

#endif
