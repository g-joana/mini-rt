#include "../../includes/minirt.h"

static void set_plane_hit(t_ray *ray, t_scene *scene, t_hit *hit)
{
	t_vec3d ray_origin;

	hit->rgb = scene->planes[hit->id].rgb;
	hit->shape_origin = scene->planes[hit->id].coord;

	// world position
	hit->position = vec_x_scalar(&ray->dir, hit->distance);
	hit->position = add_vecs(scene->cam.coord, &hit->position);

	// world direction
	hit->direction = *scene->planes[hit->id].norm;
	if (dot_vecs(&ray->dir, &hit->direction) > 0)
		hit->direction = vec_x_scalar(&hit->direction, -1);
}

static void set_cylinder_hit(t_ray *ray, t_scene *scene, t_hit *hit)
{
	// hit position in local space
	hit->position = vec_x_scalar(&ray->dir, hit->distance);
	hit->position = add_vecs(scene->cam.coord, &hit->position);

	// world normal
    t_vec3d to_hit;
    to_hit = sub_vecs(&hit->position, scene->cylinders[hit->id].coord);
	float axis_proj = dot_vecs(&to_hit, scene->cylinders[hit->id].norm);
	t_vec3d axis_component = vec_x_scalar(scene->cylinders[hit->id].norm, axis_proj);

	hit->direction = sub_vecs(&to_hit, &axis_component);
	hit->direction = norm_vec(&hit->direction);

	hit->rgb = scene->cylinders[hit->id].rgb;
	hit->shape_origin = scene->cylinders[hit->id].coord;

	if (hit->inside)
		hit->direction = vec_x_scalar(&hit->direction, -1);
}

static void set_sphere_hit(t_ray *ray, t_scene *scene, t_hit *hit)
{
	t_vec3d ray_origin;

    ray_origin = sub_vecs(scene->cam.coord, scene->spheres[hit->id].coord);
    hit->rgb = scene->spheres[hit->id].rgb;
    hit->shape_origin = scene->spheres[hit->id].coord;
    // world position
    hit->position = vec_x_scalar(&ray->dir, hit->distance);
    hit->position = add_vecs(scene->cam.coord, &hit->position);
    // world direction
    hit->direction = sub_vecs(&hit->position, hit->shape_origin);
    hit->direction = norm_vec(&hit->direction);
}

void set_shape_hit(t_ray *ray, t_scene *scene, t_hit *hit)
{
	t_vec3d ray_origin;
	t_ray local_ray;

	local_ray = *ray;
	if (!hit)
		return;
	if (hit->shape == PL)
	{
		local_ray.ori = sub_vecs(scene->cam.coord, scene->planes[hit->id].coord);
		set_plane_hit(&local_ray, scene, hit);
	}
	else if (hit->shape == SP)
	{
		local_ray.ori = sub_vecs(scene->cam.coord, scene->spheres[hit->id].coord);
		set_sphere_hit(&local_ray, scene, hit);
	}
	else if (hit->shape == CY)
	{
		// local_ray.ori = sub_vecs(scene->cam.coord, scene->cylinders[hit->id].coord);
		set_cylinder_hit(&local_ray, scene, hit);
	}
}
