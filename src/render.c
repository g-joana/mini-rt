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

uint32_t color_per_pixel(float x_origin, float y_origin)
{
	uint8_t r = (uint8_t)(x_origin * 255.0f);
	uint8_t g = (uint8_t)(y_origin * 255.0f);

	return 0xff000000 | (r << 16) | (g << 8);
}

uint32_t per_pixel(float x, float y, float z, t_scene *scene)
{
	// uint8_t r = (uint8_t)(x_origin * 255.0f);
	// uint8_t g = (uint8_t)(y_origin * 255.0f);
	//
	// return 0xff000000 | (r << 16) | (g << 8);


	// (dx^2 + dy^2)t^2 + (2(axdx + aydy))t + (ax^2 + ay^2 - r^2) = 0;


	// d -> a (ray direction) (scene->camera.normalized)
	float a = 
		x * x
		+ y * y
		+ z * z;
		//
		// scene->camera.normalized[0] * scene->camera.normalized[0]
		// + scene->camera.normalized[1] * scene->camera.normalized[1]
		// + scene->camera.normalized[2] * scene->camera.normalized[2];

	// a -> b (ray origin)
		// (
		// scene->camera.coordinates[0] * scene->camera.normalized[0]
		// + scene->camera.coordinates[1] * scene->camera.normalized[1]
		// + scene->camera.coordinates[2] * scene->camera.normalized[2]
		// );
	float b =
		2.0f *
		(
		0.0f * x
		+ 0.0f * y
		+ (-2.0f * z)
		);
		// (
		// scene->camera.coordinates[0] * x
		// + scene->camera.coordinates[1] * y
		// + scene->camera.coordinates[2] * z
		// );
		// (
		// scene->camera.coordinates[0] * scene->camera.normalized[0]
		// + scene->camera.coordinates[1] * scene->camera.normalized[1]
		// + scene->camera.coordinates[2] * scene->camera.normalized[2]
		// );
	
	(void)scene;
	// float r = scene->spheres[0].diameter/2;
	float r = 0.5f;
	float c =
		(
		0.0f * 0.0f
		+ 0.0f * 0.0f
		+ (-2.0f * -2.0f)
		) - r * r;
		// (
		// scene->camera.coordinates[0] * scene->camera.coordinates[0]
		// + scene->camera.coordinates[1] * scene->camera.coordinates[1]
		// + scene->camera.coordinates[2] * scene->camera.coordinates[2]
		// ) - (scene->spheres[0].diameter/2) * (scene->spheres[0].diameter/2);


	// discriminant = t = distance / point
	// b^2 - 4ac
	float discriminant = 
		b * b 
		- 4.0f * a * c;

	if (discriminant >= 0.0f)
		return 0xff48e448;

	return 0xff000000;
}

int    render(t_scene *scene)
{
	static int count;
	uint32_t x = 0;
	uint32_t y = 0;
	int i = 0;
	float coord[3];
	while (y < HEIGHT && i < (WIDTH * HEIGHT))
	// while (i < (WIDTH * HEIGHT))
	{
		coord[0] = ((float)x/(float)WIDTH) * 2.0f - 1.0f;
		coord[1] = ((float)y/(float)HEIGHT) * 2.0f -  1.0f;
		coord[2] = 0;
		my_mlx_pixel_put(&scene->img, x, y, per_pixel(coord[0], coord[1], -1.0f, scene));
		// my_mlx_pixel_put(&scene->img, x, y, color_per_pixel(coord[0], coord[1]));
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
	mlx_string_put(scene->mlx, scene->mlx_win, 5, 12, 0xFFFFFF, "render");
	return 0;
}
