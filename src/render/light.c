#include "../../includes/minirt.h"

uint32_t	apply_ambient(t_hit *hit, t_alight *ambient)
{
	t_vec3d	argb;

	argb = vec_x_scalar(hit->rgb, ambient->bright);
	return (color_per_pixel(&argb, 1));
}

uint32_t	apply_light(t_hit *hit, t_light *light, t_alight *ambient)
{
	t_vec3d	rgb;
	t_vec3d	ambient_rgb;
	float	intensity;
	t_vec3d	light_dir;

	light_dir = sub_vecs(light->coord, &hit->position);
	light_dir = norm_vec(&light_dir);
	light_dir = vec_x_scalar(&light_dir, -1);
	intensity = dot_vecs(&hit->direction, &light_dir);
	intensity *= light->bright;
	intensity *= -1.0f;
	intensity = clamp(intensity, 0.0f, intensity);
	ambient_rgb = vec_x_scalar(hit->rgb, ambient->bright);
	rgb = vec_x_scalar(hit->rgb, intensity * light->bright);
	rgb = add_vecs(&rgb, &ambient_rgb);
	return (color_per_pixel(&rgb, 1));
}

t_hit	*update_hit(t_hit *closest, t_hit *hit)
{
	if (closest)
		free(closest);
	closest = hit;
	return (closest);
}

t_hit	*trace_shadow(t_ray *ray, t_scene *scene)
{
	t_hit	*hit;
	t_hit	*closest;
	int		shape;
	int		count;

	shape = PL - 1;
	closest = NULL;
	while (++shape <= CY)
	{
		count = 0;
		while (count < scene->amount[shape])
		{
			hit = get_shape_hit(ray, scene, shape, count++);
			if (!closest)
				closest = hit;
			else if (hit && hit->distance > 0.001f &&
						hit->distance < closest->distance)
				closest = update_hit(closest, hit);
			else if (hit)
				free(hit);
		}
	}
	return (closest);
}

bool	in_shadow(t_hit *surface, t_scene *scene)
{
	t_hit	*hit;
	t_ray	ray;
	float	light_dist;
	t_vec3d	to_light;

	to_light = sub_vecs(scene->light.coord, &surface->position);
	light_dist = magni_vec(&to_light);
	ray.ori = vec_x_scalar(&surface->direction, 0.01f);
	ray.ori = add_vecs(&surface->position, &ray.ori);
	ray.dir = norm_vec(&to_light);
	ray.shadow = true;
	hit = trace_shadow(&ray, scene);
	if (hit)
	{
		if (hit->distance > 0.001f && hit->distance < (light_dist - 0.001f))
		{
			free(hit);
			return (true);
		}
		free(hit);
	}
	return (false);
}
