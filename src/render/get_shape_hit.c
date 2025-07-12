#include "../../includes/minirt.h"

t_hit *sphere_hit( const t_vec3d *ray_origin, const t_vec3d *ray_dir, t_sphere *sp)
{
	t_hit	*hit;
	// circle
	// (x-a)^2 + (y-b)^2 - r^2 = 0
	// quadratic eq
	// (ax^2 + ay^2)t^2 + (2(bxax + byay))t + (bx^2 + by^2 - r^2) = 0;
	float r = sp->diam/2;
	float a = dot_vecs(ray_dir, ray_dir);
	float b = 2.0f * dot_vecs(ray_origin, ray_dir);
	float c = dot_vecs(ray_origin, ray_origin) - r * r;

	// discriminant = t = hit distance / point
	// b^2 - 4ac
	float delta = b * b - 4.0f * a * c;
	if (delta < 0.0f)
		return NULL;
	hit = malloc(sizeof(t_hit));
	hit->distance = (-b - sqrtf(delta)) / (2.0f * a);
    hit->shape = SP;
	return hit;
}

t_hit *cylinder_hit( const t_vec3d *ray_origin, const t_vec3d *ray_dir, t_cylinder *cylin)
{
	t_hit	*hit;

	// all norm should be normalized on parser
	t_vec3d half_height_ratio = vec_x_scalar(cylin->norm, cylin->height / 2.0f);
	t_vec3d base = sub_vecs(cylin->coord, &half_height_ratio);
	t_vec3d top = add_vecs(cylin->coord, &half_height_ratio);
	t_vec3d cy_ori = sub_vecs(ray_origin, &base);

	float dir_axis = dot_vecs(ray_dir, cylin->norm);
	float cy_ori_axis = dot_vecs(&cy_ori, cylin->norm);


	t_vec3d dir = vec_x_scalar(cylin->norm, dir_axis);
	dir = sub_vecs(ray_dir, &dir);
	t_vec3d origin = vec_x_scalar(cylin->norm, cy_ori_axis);
	origin = sub_vecs(&cy_ori, &origin);


	float r = cylin->diam/2;
	float a = dot_vecs(&dir, &dir);
	float b = 2.0f * dot_vecs(&origin, &dir);
	float c = dot_vecs(&origin, &origin) - (r * r);
	// float c = dot_vecs(ray_origin, ray_origin) - r * r;

	// discriminant = t = hit distance / point
	// b^2 - 4ac
	float delta = b * b - 4.0f * a * c;
	if (delta < 0.0f)
		return NULL;
	hit = malloc(sizeof(t_hit));
	hit->distance = (-b - sqrtf(delta)) / (2.0f * a);
    hit->shape = CY;

	t_vec3d hit_point = {
		ray_origin->x + ray_dir->x * hit->distance,
		ray_origin->y + ray_dir->y * hit->distance,
		ray_origin->z + ray_dir->z * hit->distance
	};
	// size from base to hit point
	t_vec3d base_to_hit = sub_vecs(&hit_point, &base);
	// get height along axis
	float axis_dist = dot_vecs(&base_to_hit, cylin->norm);

	if (axis_dist < 0.0f || axis_dist > cylin->height)
	{
		free(hit);
		return NULL;
	}
	return hit;
}

t_hit *get_shape_hit(t_vec3d *ray_dir, t_scene *scene, int shape, int id)
{
	t_vec3d ray_origin;
	t_hit *hit;

    if (shape == PL)
    {
        return NULL;
    }
    else if (shape == SP)
    {
        ray_origin = sub_vecs(scene->cam.coord, scene->spheres[id].coord);
        hit = sphere_hit(&ray_origin, ray_dir, &scene->spheres[id]);
    }
    else if (shape == CY)
    {
        ray_origin = sub_vecs(scene->cam.coord, scene->cylinders[id].coord);
        hit = cylinder_hit(&ray_origin, ray_dir, &scene->cylinders[id]);
    }
    return hit;
}
