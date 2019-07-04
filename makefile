# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/04 07:02:38 by aahizi-e          #+#    #+#              #
#    Updated: 2019/07/04 08:28:35 by aahizi-e         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = fdf

SRCS = main.c\
	   base_utils.c\
	   file_utils.c\
	   map_info.c\
	   mlx_function.c\
	   draw.c

FLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a
LIBMLX = minilibx_macos/libmlx.a

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) 
	make -C libft/
	make -C minilibx_macos/
	$(CC) $(FLAGS) $(LIBFT) $(LIBMLX) $^ -o $@ -framework OpenGl -framework AppKit

sani: $(OBJS) 
	make -C libft/
	make -C minilibx_macos/
	$(CC) $(FLAGS) -fsanitize=address $(LIBFT) $(LIBMLX) $^ -o $(NAME) -framework OpenGl -framework AppKit

clean:
	rm -rf $(OBJS)
	make clean -C libft/
	make clean -C minilibx_macos/

fclean: clean
	rm -rf $(NAME)

re: fclean all
