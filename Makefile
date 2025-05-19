NAME		= minirt

# Directories
SRC_DIR		= src
INC_DIR		= includes
OBJ_DIR		= obj
LIBFT_DIR	= libft
MLX_DIR		= mlx

# Sources
SRCS		= main.c parser.c free.c error.c init.c init2.c set_properties.c

# Object files
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Compiler
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -ggdb3

# Libraries
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= -L$(MLX_DIR) -lXext -lX11 -lm

# Targets
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
