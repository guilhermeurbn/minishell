# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guisanto <guisanto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/18 16:49:40 by guisanto          #+#    #+#              #
#    Updated: 2026/02/07 16:19:36 by guisanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCDIRS = src
SRCS = $(shell find $(SRCDIRS) -type f -name "*.c")
OBJS = $(SRCS:.c=.o)

PIPEX_DIR = library/pipex
LIBFT_DIR = $(PIPEX_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -lreadline $(LIBFT)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all