#include "../includes/minirt.h"

void	start_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	scene->mlx_win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "minirt");
	scene->img.img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	scene->img.addr = mlx_get_data_addr(scene->img.img, &scene->img.bits_per_pixel,
			&scene->img.line_len, &scene->img.endian);
	mlx_key_hook(scene->mlx_win, key_hook, scene);
	// mlx_hook(scene->mlx_win, 17, 1L << 17, mouse_hook, scene);
}

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
