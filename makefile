# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/04 07:02:38 by aahizi-e          #+#    #+#              #
#    Updated: 2019/07/12 14:22:15 by aahizi-e         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = fdf

SRCS = main.c\
	   file_helper.c\
	   base_helper.c\
	   depth_color_helper.c\
	   draw.c\
	   loop_mlx.c\
	   matrix.c\

FLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a
LIBMLX = minilibx_macos/libmlx.a

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) 
	make -C libft/
	make -C minilibx_macos/
	$(CC) $(FLAGS) $(LIBFT) $(LIBMLX) $^ -o $@ -framework OpenGl -framework AppKit -lm

sani: $(OBJS) 
	make -C libft/
	make -C minilibx_macos/
	$(CC) $(FLAGS) -fsanitize=address $(LIBFT) $(LIBMLX) $^ -o $(NAME) -framework OpenGl -framework AppKit -lm

clean:
	rm -rf $(OBJS)
	make clean -C libft/
	make clean -C minilibx_macos/

fclean: clean
	rm -rf $(NAME)

re: fclean all
