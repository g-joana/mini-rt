#include "../includes/minirt.h"
#include <stdio.h>

int main(int argc, char **argv) {

    t_scene scene;

    if (argc != 2)
        exit_error(NULL, "no file", 1);
    scene = parse(argv[1]);
    if (scene.planes == NULL)
        ft_printf("NULL scene\n");
    free_scene(&scene);
    return (0);
}
