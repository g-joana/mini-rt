#include "../../includes/minirt.h"

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

t_vec3d rotate_to_z_axis(t_vec3d *v, t_vec3d *norm) {

    t_vec3d z_axis = {0, 0, 1};
    *norm = norm_vec(norm);
    float cos_theta = dot_vecs(norm, &z_axis);
    if (cos_theta > 0.9999f) // already aligned
        return *v;
    if (cos_theta < -0.9999f) // opposite direction
        return (t_vec3d){-v->x, -v->y, -v->z};

    float theta = acosf(cos_theta);
    t_vec3d axis = cross_vecs(norm, &z_axis);
    axis = norm_vec(&axis);

    float c = cosf(theta);
    float s = sinf(theta);

    t_vec3d v_rot;
    v_rot.x = v->x * c + axis.x * dot_vecs(&axis, v) * (1 - c) + (-axis.z * v->y + axis.y * v->z) * s;
    v_rot.y = v->y * c + axis.y * dot_vecs(&axis, v) * (1 - c) + ( axis.z * v->x - axis.x * v->z) * s;
    v_rot.z = v->z * c + axis.z * dot_vecs(&axis, v) * (1 - c) + (-axis.y * v->x + axis.x * v->y) * s;
    return v_rot;
}

t_hit *cylinder_hit(t_ray *ray, t_cylinder *cy)
{
	t_hit	*hit;

	t_vec3d dir;
	t_vec3d ori; 

	dir = rotate_to_z_axis(&ray->dir, cy->norm);
	dir.z = 0;
	ori = rotate_to_z_axis(&ray->ori, cy->norm);
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
	hit->position = vec_x_scalar(&ray->dir, hit->distance);
	hit->position = add_vecs(&ray->ori, &hit->position);

	// define limits
	t_vec3d half_height_ratio = vec_x_scalar(cy->norm, cy->height / 2.0f);
	t_vec3d base = sub_vecs(cy->coord, &half_height_ratio);
	t_vec3d center = sub_vecs(&hit->position, cy->coord);
	float len = dot_vecs(&center, cy->norm);
	if (len < -cy->height/2.0f || len > cy->height /2.0f)
	{
		free(hit);
		return NULL;
	}
	hit->shape = CY;
	t_vec3d axis = vec_x_scalar(cy->norm, len);
	hit->direction = sub_vecs(&center, &axis);
	hit->direction = norm_vec(&hit->direction);
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
