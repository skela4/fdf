# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/04 07:02:38 by aahizi-e          #+#    #+#              #
#    Updated: 2019/07/13 09:50:10 by clboutry         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = fdf

SRCS = main.c\
	   file_helper.c\
	   color_helper.c\
	   base_helper.c\
	   mlx_helper.c\
	   key_helper.c\
	   rotation.c\
	   projection.c\
	   draw.c\
	   apply.c\
	   matrix.c\
	   memory.c\

FLAGS = -Wall -Wextra -Werror


LIBFT = libft/libft.a
LIBMLX = minilibx_macos/libmlx.a

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) fdf.h 
	make -C libft/
	make -C minilibx_macos/
	$(CC) $(FLAGS) $(LIBFT) $(LIBMLX) $(OBJS) -o $@ -framework OpenGl -framework AppKit -lm

clean:
	rm -rf $(OBJS)
	make clean -C libft/
	make clean -C minilibx_macos/

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft/

re: fclean all
