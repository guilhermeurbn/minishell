# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scootergui <scootergui@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/24 18:14:23 by scootergui        #+#    #+#              #
#    Updated: 2026/01/21 14:42:24 by scootergui       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c srcs/parsing.c srcs/signs.c srcs/lexer.c srcs/utils_lexer.c

OBJS = $(SRCS:.c=.o)

CC = @cc
CFLAGS = -g -Wall -Wextra -Werror
LDFLAGS = -lreadline -lncurses
RM = rm -f

LIBFT_PATH = ./Libft
LIBFT = $(LIBFT_PATH)/libft.a

NAME = mini_shell

all : $(NAME)
$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS)  $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	@echo " [ .. ] | Compiling.."
	@make -s -C $(LIBFT_PATH)
	@echo " [ OK ] | Ready!"

clean:
	@$(RM) $(OBJS)
	@$(RM) $(LIBFT_PATH)/*.o
	@echo "all objects were removed"

fclean: clean
	@$(RM) $(NAME)
	@make -s fclean -C $(LIBFT_PATH)
	clear
	@echo "all files were removed"

re: fclean $(NAME)
	clear
	@echo "bla bla bla"
.PHONY: all clean fclean re bonus
