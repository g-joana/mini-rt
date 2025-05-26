#include "../includes/minirt.h"

void	start_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	scene->mlx_win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "minirt");
	scene->img.img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	scene->img.addr = mlx_get_data_addr(scene->img.img, &scene->img.bits_per_pixel,
			&scene->img.line_length, &scene->img.endian);
	// mlx_key_hook(scene->mlx_win, key_hook, scene);
	// mlx_hook(scene->mlx_win, 17, 1L << 17, mouse_hook, scene);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

void	my_mlx_pixel_put2(t_data *data, int px, int color)
{
	char	*dest;

	dest = data->addr + (px * (data->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

int    render(t_scene *scene)
{
	static int count;
	int x = 0;
	int y = 0;
	int i = 0;
	while (y < HEIGHT && i < (WIDTH * HEIGHT))
	// while (i < (WIDTH * HEIGHT))
	{
		// +- vb^2 - 4ac
		// (ax + dx.t)^2 + (ay + dy.t)^2 + (az + dz.t)^2 - r^2 = 0;


		// int p[3];
		// pxy = axy + dxy.t
		// p[0] = a[0] + d[x].t;
		//
		// t - distance
		// int t =  
		// p[0] = scene->camera.coordinates[0] + (scene->camera.normalized[0] * t);
		my_mlx_pixel_put(&scene->img, x, y, 0x48E448);
		// my_mlx_pixel_put2(&scene->img, i, 0x48E448);
		x++;
		i++;
		if (x == WIDTH)
			y++;
		if (x == WIDTH)
			x = 0;
		count++;
		printf("%i\n", count);
	}
    mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->img.img, 0, 0);
	return 0;
}

