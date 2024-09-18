# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaguen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/05 06:10:54 by  souaguen         #+#    #+#              #
#    Updated: 2024/09/18 03:13:47 by souaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
SRCS=main.c
NAME=miniRT
OBJ=$(SRCS:.c=.o)
CFLAGS=-I./
LIBFLAGS=-L./minilibx-linux -l:libmlx_Linux.a -lXext -lX11 -lm -L./libft -l:libft.a

$(NAME): $(OBJ)
	make -C libft all bonus
	make -C minilibx-linux all
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFLAGS) 

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
