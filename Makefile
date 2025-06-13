NAME		= minirt

# Directories
SRC_DIR		= src
INC_DIR		= includes
OBJ_DIR		= obj
LIBFT_DIR	= libft
MLX_DIR		= mlx
PARS_DIR	= $(SRC_DIR)/parser
VEC_DIR		= trivec

# Sources
SRCS		= main.c free.c error.c print.c render.c

# Parser files
PARS		= init.c init_utils_scene.c init_utils_shapes.c parser.c \
			  set_properties.c set_scene.c set_shapes.c \

# Object files
OBJS		= \
			$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o)) \
			$(addprefix $(OBJ_DIR)/, $(PARS:.c=.o))

# Compiler
CC			= gcc
# CFLAGS		= -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(VEC_DIR) -ggdb3
CFLAGS		= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(VEC_DIR) -ggdb3 -g

# Libraries
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a -lXext -lX11 -lm
VEC			= $(VEC_DIR)/trivec.a

# Targets
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(VEC) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(VEC) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# src files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# parser files
$(OBJ_DIR)/%.o: $(PARS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(VEC):
	make -C $(VEC_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean
	make -C $(VEC_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(VEC_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
