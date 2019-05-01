# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/20 15:47:19 by aahizi-e          #+#    #+#              #
#    Updated: 2019/02/02 15:37:23 by aahizi-e         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = fdf

SRCS = main.c

FLAGS = -Wall -Wextra -Werror

LIBFT = -L libft -lft

LIBMLX = -L minilibx_macos -lmlx

GRAPHICS = -framework OpenGL -framework AppKit

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft/
	@$(CC) $(CFLAGS) $(LIBFT) $(LIBMLX) $(GRAPHICS) $^ -o $@

clean:
	@rm -rf $(OBJS)
	@make clean -C libft/

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft/

re: fclean all