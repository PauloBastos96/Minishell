# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffilipe- <ffilipe-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/09 15:23:17 by paulorod          #+#    #+#              #
#    Updated: 2023/08/24 10:37:59 by ffilipe-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= minishell.c \
	srcs/builtins/builtin_export.c \
	srcs/builtins/builtin_unset.c \
	srcs/builtins/builtins.c \
	srcs/builtins/utils.c \
	srcs/utils/commands.c \
	srcs/utils/signals.c \
	srcs/utils/utils.c \
	srcs/utils/pipes_utils.c \
	srcs/pipes/handle_pipes.c

OBJS	= $(SRCS:.c=.o)

NAME	= minishell

CC		= cc

CFLAGS	= -Wall -Wextra -Werror #-g -fsanitize=address

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
