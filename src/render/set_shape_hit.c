#include "../../includes/minirt.h"

void set_cylinder_hit(t_scene *scene, t_hit *hit)
{
	hit->rgb = scene->cylinders[hit->id].rgb;
	hit->shape_origin = scene->cylinders[hit->id].coord;
}

void set_sphere_hit(t_ray *ray, t_scene *scene, t_hit *hit)
{
	t_vec3d ray_origin;

    ray_origin = sub_vecs(scene->cam.coord, scene->spheres[hit->id].coord);
    hit->rgb = scene->spheres[hit->id].rgb;
    hit->shape_origin = scene->spheres[hit->id].coord;
    hit->position = vec_x_scalar(&ray->dir, hit->distance);
    hit->position = add_vecs(&ray_origin, &hit->position);
    hit->direction = norm_vec(&hit->position);
}

void set_shape_hit(t_ray *ray, t_scene *scene, t_hit *hit)
{
	t_vec3d ray_origin;

    if (!hit)
        return;
    if (hit->shape == PL)
    {
        return;
    }
    else if (hit->shape == SP)
    {
		set_sphere_hit(ray, scene, hit);
    }
    else if (hit->shape == CY)
    {
		set_cylinder_hit(scene, hit);
    }
}
