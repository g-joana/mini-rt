#include "../../includes/minirt.h"

/* returns closest hit of scene objs */
t_hit *trace_ray(t_ray *ray, t_scene *scene)
{
	t_hit *hit;
	t_hit *closest = NULL;
	int shape = PL;
	float distance = FLT_MAX;
	int count;

	while (shape <= CY)
	{
		count = 0;
		while (count < scene->amount[shape])
		{
			hit = get_shape_hit(ray, scene, shape, count);
			if (hit && hit->distance > 0.0f && hit->distance < distance)
			{
				if (closest)
					free(closest);
				distance = hit->distance;
				closest = hit;
				closest->id = count;
			}
			else
				free(hit);
			count++;
		}
		shape++;
	}
	set_shape_hit(ray, scene, closest);
	return closest;
}

t_vec3d	get_direction(float x, float y, t_scene *scene) {
	float u;
	float v;

	scene->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	scene->scale = tanf((scene->cam.fov / 2.0f) * (M_PI / 180.0f));

	u = (x/(float)WIDTH);
	v = (y/(float)HEIGHT);
	u = (u * 2.0f - 1.0f) * scene->aspect_ratio * scene->scale;
	v = (v * 2.0f - 1.0f) * scene->scale;

	t_vec3d x_dir = vec_x_scalar(scene->cam.right, u);
	t_vec3d y_dir = vec_x_scalar(scene->cam.up, v);

	t_vec3d ray_dir = add_vecs(&x_dir, &y_dir);
	ray_dir = add_vecs(&ray_dir, scene->cam.foward);
	ray_dir = norm_vec(&ray_dir);

	return ray_dir;
}

u_int32_t	perpixel(float x, float y, t_scene* scene) // raygen -> ray trace pipeline / shaders
{
    u_int32_t color;
    t_hit *closest_hit;
    t_ray ray;

    ray.dir = get_direction(x, y, scene);
    ray.shadow = false;
    closest_hit = trace_ray(&ray, scene);
    if (!closest_hit)
	color = 0xff007fff; // background / miss shader
    else
    {
	// color = apply_light(closest_hit, &scene->light, &scene->amb_light);
	if (!in_shadow(closest_hit, scene))
	    color = apply_light(closest_hit, &scene->light, &scene->amb_light);
	else
	    color = apply_ambient(closest_hit, &scene->amb_light);
    }
    free(closest_hit);
    return color;
}

int		render(t_scene *scene)
{
	static int count;
	float x = 0;
	float y = 0;
	t_hit *hit;
	u_int32_t color;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = perpixel(x, y, scene);
			my_mlx_pixel_put(&scene->img, x, y, color);
			x++;
		}
		y++;
	}
	count++;
	// printf("%i\n", count);
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->img.img, 0, 0);
	// mlx_string_put(scene->mlx, scene->mlx_win, 5, 12, 0xFFFFFF, "render");
	return 0;
}
