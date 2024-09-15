# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaguen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/05 06:10:54 by  souaguen         #+#    #+#              #
#    Updated: 2024/09/15 10:50:14 by souaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
SRCS=main.c
NAME=miniRT
OBJ=$(SRCS:.c=.o)
CFLAGS=-Wall -Werror -Wextra -I./

$(NAME): $(OBJ)
	make -C libft all bonus
	make -C minilibx-linux all
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lm -L./minilibx-linux -l:libmlx_Linux.a

all: $(NAME)

clean:
	make -C libft clean
	make -C minilibx-linux clean
	rm -f $(OBJ)
fclean: clean
	make -C libft fclean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re bonus
