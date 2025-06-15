#include "../includes/minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_len + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

float clamp(float n, float min, float max){

	if (n < min)
		return min;
	if (n > max)
		return max;
	return n;
}

float clamp_color(float n){

	if (n < 0)
		return 0;
	if (n > 1)
		return 1;
	return n;
}

uint32_t color_per_pixel(t_vec3d *vec, float alpha)
{
	uint8_t r = (uint8_t)(clamp_color(vec->x) * 255.0f);
	uint8_t g = (uint8_t)(clamp_color(vec->y) * 255.0f);
	uint8_t b = (uint8_t)(clamp_color(vec->z) * 255.0f);
	uint8_t a = (uint8_t)(clamp_color(alpha) * 255.0f);

	return (a << 24) | (r << 16) | (g << 8) | b;
}

uint32_t per_pixel(float x, float y, t_scene *scene)
{
	// uint8_t r = (uint8_t)(x_origin * 255.0f);
	// uint8_t g = (uint8_t)(y_origin * 255.0f);
	//
	// return 0xff000000 | (r << 16) | (g << 8);

	// ray direction
	// x = scene->cam.norm->x;
	// y = scene->cam.norm->y;
	// float z = scene->cam.norm->z;

	(void)scene;
	// (dx^2 + dy^2)t^2 + (2(axdx + aydy))t + (ax^2 + ay^2 - r^2) = 0;
	const t_vec3d ray_origin = {0, 0, 1.0f};
	const t_vec3d ray_dir = {x, y, -1.0f};
	// const t_vec3d ray_origin = {
	// 	scene->cam.coord->x,
	// 	scene->cam.coord->y,
	// 	scene->cam.coord->z
	// };
	// float r = scene->spheres[0].diam/2;
	float r = 0.10f;

	// d -> a (ray direction)
	float a = dot_vecs(&ray_dir, &ray_dir);

	// a -> b (ray origin)
	float b = 2.0f * dot_vecs(&ray_origin, &ray_dir);
	
	// c -> obj?
	float c = dot_vecs(&ray_origin, &ray_origin) - r * r;

	// discriminant = t = hit distance / point
	// b^2 - 4ac
	float delta = b * b - 4.0f * a * c;

	if (delta < 0.0f)
		return 0xff000000;
	// float t0 = (-b - sqrtf(discriminant)) / (2.0f * a);
	// float t1 = (+b - sqrtf(discriminant)) / (2.0f * a);

	float t0 = (-b - sqrtf(delta)) / (2.0f * a);
	// float t1 = (-b + sqrtf(delta)) / (2.0f * a);
	// float n[3];
	// n[0] = x - scene->spheres[0].coordinates[0];
	// n[1] = y - scene->spheres[1].coordinates[2];
	// n[2] = z - scene->spheres[3].coordinates[3];

	t_vec3d hitpos;
	hitpos.x = ray_origin.x + ray_dir.x * t0;
	hitpos.y = ray_origin.y + ray_dir.y * t0;
	hitpos.z = ray_origin.z + ray_dir.z * t0;
	t_vec3d norm;
	norm.x = hitpos.x - scene->spheres[0].coord->x;
	norm.y = hitpos.y - scene->spheres[0].coord->y;
	norm.z = hitpos.z - scene->spheres[0].coord->z;
	norm = norm_vec(&norm);
	// ajusts color channels to appear equal
	// norm.x = norm.x * 0.5f + 0.5f;
	// norm.y = norm.y * 0.5f + 0.5f;
	// norm.z = norm.z * 0.5f + 0.5f;

    t_vec3d light_dir = {-1, -1, -1};
    

    light_dir = norm_vec(&light_dir);

    // negative light dir
    light_dir = vec_x_scalar(&light_dir, -1);
    float d = dot_vecs(&norm, &light_dir); // == cos(angle) | if angle > 90 = negative result | cos(90) == 0
    // dot product = always in -1->1 range
    // this angle is the surface angle - reflects the light

    // clamping only min, so there is no negative (if angle > 90)
    d = clamp(d, 0.0f, d);

    t_vec3d sphere_color = {0.5, 0, 0.5};
    sphere_color = vec_x_scalar(&sphere_color, d);
	return (color_per_pixel(&sphere_color, 1));
}

int		render(t_scene *scene)
{
	static int	count;
	uint32_t 	x = 0;
	uint32_t 	y = 0;
	int 		i = 0;
	float coord[3];
	while (y < HEIGHT && i < (WIDTH * HEIGHT))
	// while (i < (WIDTH * HEIGHT))
	{
        // 0 -> 1 range
		coord[0] = ((float)x/(float)WIDTH);
		coord[1] = ((float)y/(float)HEIGHT);
		// z is the ray direction (1 or -1)
		// remap screen coords so xy(0,0) is in the middle
		coord[0] = coord[0] * 2.0f - 1.0f;
		coord[1] = (1.0 - coord[1]) * 2.0f - 1.0f;
		my_mlx_pixel_put(&scene->img, x, y, per_pixel(coord[0], coord[1], scene));
		// my_mlx_pixel_put(&scene->img, x, y, color_per_pixel(coord[0], coord[1]));
		// my_mlx_pixel_put2(&scene->img, i, 0x48E448);
		x++;
		i++;
		if (x == WIDTH)
		{
			y++;
			x = 0;
		}
		count++;
		// printf("%i\n", count);
	}
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->img.img, 0, 0);
	// mlx_string_put(scene->mlx, scene->mlx_win, 5, 12, 0xFFFFFF, "render");
	return 0;
}
