# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaguen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/05 06:10:54 by  souaguen         #+#    #+#              #
#    Updated: 2024/09/21 10:35:57 by souaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
SRCS=src/utils.c \
     main.c
NAME=miniRT
OBJ=$(SRCS:.c=.o)
CFLAGS=-I./includes -g
LIBFLAGS=-L./minilibx-linux -l:libmlx_Linux.a -lXext -lX11 -lm

$(NAME): $(OBJ)
	make -C minilibx-linux all
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFLAGS) 

all: $(NAME)

clean:
	make -C minilibx-linux clean
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re bonus
