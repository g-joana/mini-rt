#include "../../includes/minirt.h"
#include <stdio.h>

t_hit *sphere_hit(t_ray *ray, t_sphere *sp)
{
	t_hit	*hit;
	// circle
	// (x-a)^2 + (y-b)^2 - r^2 = 0
	// quadratic eq
	// (ax^2 + ay^2)t^2 + (2(bxax + byay))t + (bx^2 + by^2 - r^2) = 0;
	float r = sp->diam/2;
	float a = dot_vecs(&ray->dir, &ray->dir);
	float b = 2.0f * dot_vecs(&ray->ori, &ray->dir);
	float c = dot_vecs(&ray->ori, &ray->ori) - r * r;

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

t_vec3d transform_to_z_axis(t_vec3d *v, t_vec3d *norm, int clock) {

    t_vec3d z_axis = {0, 0, 1};
    *norm = norm_vec(norm);
    float cos_theta = dot_vecs(norm, &z_axis);
    if (cos_theta > 0.0001f) // already aligned
        return *v;
    if (cos_theta < -0.0001f) // opposite direction
        return (t_vec3d){-v->x, -v->y, -v->z};

    float theta = acosf(cos_theta);
    t_vec3d axis;
    axis = cross_vecs(norm, &z_axis);
    axis = norm_vec(&axis);

    if (clock == -1)
        theta = -theta;
    float c = cosf(theta);
    float s = sinf(theta);

    t_vec3d transform;
    transform.x = v->x * c + axis.x * dot_vecs(&axis, v) * (1 - c) + (-axis.z * v->y + axis.y * v->z) * s;
    transform.y = v->y * c + axis.y * dot_vecs(&axis, v) * (1 - c) + ( axis.z * v->x - axis.x * v->z) * s;
    transform.z = v->z * c + axis.z * dot_vecs(&axis, v) * (1 - c) + (-axis.y * v->x + axis.x * v->y) * s;
    return transform;
}

t_hit *cylinder_hit(t_ray *ray, t_cylinder *cy)
{
	t_hit	*hit;

	t_vec3d dir;
	t_vec3d ori; 

	// *cy->norm = norm_vec(cy->norm);
	dir = transform_to_z_axis(&ray->dir, cy->norm, 1);
	dir.z = 0;
	ori = transform_to_z_axis(&ray->ori, cy->norm, 1);
	ori.z = 0;

	float r = cy->diam/2;
	float a = dot_vecs(&dir, &dir);
	float b = 2.0f * dot_vecs(&ori, &dir);
	float c = dot_vecs(&ori, &ori) - r * r;

	float delta = b * b - 4.0f * a * c;
	if (delta < 0.0f)
		return NULL;
	float t = (-b - sqrtf(delta)) / (2.0f * a);
	if (t < 0.0f)
		return NULL;

	hit = malloc(sizeof(t_hit));
	hit->distance = t;
    // local position
	hit->position = vec_x_scalar(&ray->dir, hit->distance);
	hit->position = add_vecs(&ray->ori, &hit->position);

	t_vec3d center = sub_vecs(&hit->position, cy->coord);
	float len = dot_vecs(&center, cy->norm);
	if (len < -cy->height/2.0f || len > cy->height /2.0f)
	{
		free(hit);
		return NULL;
	}
	t_vec3d axis = vec_x_scalar(cy->norm, len);
    // local normal
	hit->direction = sub_vecs(&center, &axis);
    hit->direction = cross_vecs(&hit->position, cy->norm);
	hit->direction = norm_vec(&hit->direction);
    // world normal
    hit->position = transform_to_z_axis(&hit->position, cy->norm, -1);
    hit->direction = transform_to_z_axis(&hit->direction, cy->norm, -1);
	hit->direction = norm_vec(&hit->direction);
	hit->shape = CY;
	return hit;
}

t_hit *get_shape_hit(t_ray *ray, t_scene *scene, int shape, int id)
{
	t_hit *hit;

	if (shape == PL)
	{
		return NULL;
	}
	else if (shape == SP)
	{
		ray->ori = sub_vecs(scene->cam.coord, scene->spheres[id].coord);
		hit = sphere_hit(ray, &scene->spheres[id]);
	}
	else if (shape == CY)
	{
		ray->ori = sub_vecs(scene->cam.coord, scene->cylinders[id].coord);
		hit = cylinder_hit(ray, &scene->cylinders[id]);
	}
	return hit;
}
