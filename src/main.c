#include "../includes/minirt.h"
// checar leaks

int main(int argc, char **argv) {

    t_scene *scene;

    if (argc != 2)
        exit_error(NULL, "no file", 1);
    scene = parse(argv[1]);
    // print_scene(scene);
	start_mlx(scene);
    mlx_loop_hook(scene->mlx, render, scene);
    mlx_loop(scene->mlx);
    free_scene(scene);
    return (0);
}
