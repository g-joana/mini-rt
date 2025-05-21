#include "../includes/minirt.h"
// checar leaks

int main(int argc, char **argv) {

    t_scene *scene;

    if (argc != 2)
        exit_error(NULL, "no file", 1);
    scene = parse(argv[1]);
    print_scene(scene);
    free_scene(scene);
    return (0);
}
