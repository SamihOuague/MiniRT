# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaguen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 10:21:22 by souaguen          #+#    #+#              #
#    Updated: 2024/10/22 12:19:59 by souaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-g -I./ -I./get_next_line -I./libft -I./minilibx-linux  
SRC=ft_sphere_utils.c \
    ft_cylinder_utils.c \
    ft_plane_utils.c \
    ft_shapes.c \
    ft_utils.c \
    get_next_line/get_next_line.c \
    get_next_line/get_next_line_utils.c \
    main.c
OBJ=$(SRC:.c=.o)
NAME=miniRT

$(NAME): $(OBJ)
	make -C minilibx-linux
	make -C libft all bonus
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME) -L./libft -l:libft.a -L./minilibx-linux -l:libmlx.a -lmlx -lXext -lX11 -lm

clean:
	make -C libft clean	
	make -C minilibx-linux clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean re
