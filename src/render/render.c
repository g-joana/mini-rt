#include "../../includes/minirt.h"
#include <stdio.h>

uint32_t apply_ambient(t_hit *hit, t_alight *ambient)
{
	t_vec3d argb;
	argb = vec_x_scalar(hit->rgb, ambient->bright);
	return (color_per_pixel(&argb, 1));
}

uint32_t apply_light(t_hit *hit, t_light *light, t_alight *ambient)
{
	hit->direction = norm_vec(&hit->direction); // do this on parser
	t_vec3d light_dir = sub_vecs(light->coord, &hit->position);
	light_dir = norm_vec(&light_dir);

	light_dir = vec_x_scalar(&light_dir, -1);
	float light_intensity = dot_vecs(&hit->direction, &light_dir); 
	light_intensity = light_intensity  * -1.0f;
	light_intensity = clamp(light_intensity, 0.0f, light_intensity);
	t_vec3d rgb;
	t_vec3d argb;
	argb = vec_x_scalar(hit->rgb, ambient->bright);
	rgb = vec_x_scalar(hit->rgb, light_intensity * light->bright);
	rgb = add_vecs(&rgb , &argb);
	return (color_per_pixel(&rgb, 1));
}

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

t_hit *trace_shadow(t_ray *ray, t_scene *scene)
{
	t_hit *hit;
	int shape = PL;
	int count;

	while (shape <= CY)
	{
		count = 0;
		while (count < scene->amount[shape])
		{
			hit = get_shape_hit(ray, scene, shape, count);
			if (hit)
			{
                hit->id = count;
                return (hit);
			}
            free(hit);
			count++;
		}
		shape++;
	}
	return NULL;
}

bool in_shadow(t_hit *surface, t_scene *scene)
{
	t_hit *hit;
    t_ray ray;
	float light_distance;

	t_vec3d diff = sub_vecs(scene->light.coord, &surface->position);
	light_distance = magni_vec(&diff);
    // ray.ori = surface->position;
    ray.ori = vec_x_scalar(&surface->direction, 1e4);
    ray.ori = add_vecs(&surface->position, &ray.ori);
    ray.dir = sub_vecs(scene->light.coord, &ray.ori);
    ray.dir = norm_vec(&ray.dir);
    ray.shadow = true;
    // printf("\n\n");
    // printf("surface position:  %f  %f  %f\n", surface->position.x, surface->position.y, surface->position.z);
    // printf("light position:  %f  %f  %f\n", scene->light.coord->x, scene->light.coord->y, scene->light.coord->z);
    // printf("\n");
    // printf("light distance:  %f\n", light_distance);
    // printf("ray origin:  %f  %f  %f\n", ray.ori.x, ray.ori.y, ray.ori.z);
    // printf("ray dir:  %f  %f  %f\n", ray.dir.x, ray.dir.y, ray.dir.z);
    hit = trace_shadow(&ray, scene);
    if (hit)
    {
		if (hit->id != surface->id && hit->shape != surface->shape)
        {
            if (hit->distance < light_distance)
            {
                free(hit);
                return true;
            }
        }
        free(hit);
    }
    return false;
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
