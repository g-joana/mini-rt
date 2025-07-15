FLAGS = -Wall -Wextra -Werror -c
NAME = trivec.a
FILES_C	= add_vecs.c dot_vecs.c magni_vec.c norm_vec.c sub_vecs.c vec_x_scalar.c cross_vecs.c
FILES_O = $(FILES_C:.c=.o)

all: $(NAME)

.c.o:
	cc $(FLAGS) $< -o $@

$(NAME): $(FILES_O)
	ar -rc $(NAME) $(FILES_O)

exec: $(FILES_C)
	cc -Wall -Wextra -Werror -o -c exec $(FILES_C)

clean:
	rm -rf $(FILES_O)

fclean: clean
	rm -rf $(NAME)

re: fclean all
