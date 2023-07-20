# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 11:33:18 by paulorod          #+#    #+#              #
#    Updated: 2023/05/25 14:21:47 by paulorod         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
BONUS = ft_lstadd_back_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstmap_bonus.c \
	ft_lstnew_bonus.c \
	ft_lstsize_bonus.c
SRCS = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_free.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	get_next_line.c \
	ft_printf.c \
	ft_print_char.c \
	ft_print_formats.c \
	ft_print_hex.c \
	ft_print_nbrs.c \
	ft_print_percentage.c \
	ft_print_pointer.c \
	ft_print_strings.c
SRCS_OBJECTS = $(SRCS:.c=.o)
BONUS_OBJECTS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS_OBJECTS)
	ar -rcs $(NAME) $(SRCS_OBJECTS)
bonus: $(SRCS_OBJECTS) $(BONUS_OBJECTS)
	ar -rcs $(NAME) $(SRCS_OBJECTS) $(BONUS_OBJECTS)
clean:
	rm -f $(SRCS_OBJECTS) $(BONUS_OBJECTS)
fclean: clean
	rm -f $(NAME)
re: fclean all
