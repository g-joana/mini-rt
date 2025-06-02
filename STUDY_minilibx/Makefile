# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nranna <nranna@student.42.rio>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/25 20:32:31 by nranna            #+#    #+#              #
#    Updated: 2025/05/26 12:57:21 by nranna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CCFLAGS = -O3 -Wall -Wextra -Werror -lm
MINILIBX_FLAGS = -L../mlx -lmlx -lXext -lX11 -lz

NAME = executable
MINILIBX = ../mlx/libmlx.a

SRC = ex01.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CCFLAGS) -c -o $@ $<

$(NAME): $(OBJ) $(MINILIBX)
	@$(CC) $(CCFLAGS) $(OBJ) $(MINILIBX) $(MINILIBX_FLAGS) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
