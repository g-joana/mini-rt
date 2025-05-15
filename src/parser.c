#include "../includes/minirt.h"

void ft_error(char *msg, int ret)
{
    ft_putstr_fd(msg, 2);
    //free
    exit(ret);
}

float   ft_atof(char *str)
{

}

t_scene    *parse(int argc, char **argv) {
    if (argc != 2)
        ft_error("input: [file.rt]", 1);
    // lexer
    int fd = open(argv[1], O_RDONLY);
    char *line = get_next_line(fd);
    while (line)
    {
        char **properties = ft_split(line, ' ');

    }
    close(fd);
    // parser
}

