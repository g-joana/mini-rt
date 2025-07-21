#include "../../includes/minirt.h"

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

t_hit *trace_shadow(t_ray *ray, t_scene *scene)
{
    t_hit *hit;
    t_hit *closest = NULL;
    int shape = PL;
    int count;
    float closest_distance = FLT_MAX;
    
    while (shape <= CY)
    {
        count = 0;
        while (count < scene->amount[shape])
        {
            hit = get_shape_hit(ray, scene, shape, count);
            if (hit && hit->distance > 0.001f && hit->distance < closest_distance)
            {
                if (closest)
                    free(closest);
                closest_distance = hit->distance;
                closest = hit;
                closest->id = count;
                closest->shape = shape;
            }
            else if (hit)
                free(hit);
            count++;
        }
        shape++;
    }
    return closest;
}

bool in_shadow(t_hit *surface, t_scene *scene)
{
    t_hit *hit;
    t_ray ray;
    float light_distance;
    
    t_vec3d to_light = sub_vecs(scene->light.coord, &surface->position);
    light_distance = magni_vec(&to_light);
    
    ray.ori = vec_x_scalar(&surface->direction, 0.01f);
    ray.ori = add_vecs(&surface->position, &ray.ori);
    ray.dir = norm_vec(&to_light);
    ray.shadow = true;
    
    hit = trace_shadow(&ray, scene);
    if (hit)
    {
        if (hit->distance > 0.001f && hit->distance < (light_distance - 0.001f))
        {
            free(hit);
            return true;
        }
        free(hit);
    }
    return false;
}
