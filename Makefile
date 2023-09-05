# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/09 15:23:17 by paulorod          #+#    #+#              #
#    Updated: 2023/09/05 13:09:20 by ffilipe-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= minishell.c \
	srcs/builtins/builtin_export.c \
	srcs/builtins/builtin_unset.c \
	srcs/builtins/builtins.c \
	srcs/builtins/env_utils.c \
	srcs/builtins/utils.c \
	srcs/utils/command_utils.c \
	srcs/utils/commands.c \
	srcs/utils/command_parser.c \
	srcs/utils/paths.c \
	srcs/utils/signals.c \
	srcs/utils/utils.c \
	srcs/utils/pipes_utils.c \
	srcs/pipes/handle_pipes.c \
	srcs/utils/node_utils.c \
	srcs/redirections/handle_redirections.c \
	srcs/redirections/heredoc.c \
	srcs/execution/exec.c

OBJS	= $(SRCS:.c=.o)

NAME	= minishell

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -g

RM		= rm -rf

LIBFT_PATH = ./Libft

LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $^ -lreadline -o $@

$(LIBFT):
	make -C $(LIBFT_PATH) all
	make -C $(LIBFT_PATH) bonus

clean:
	make -C $(LIBFT_PATH) clean
	$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)
		make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
