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

t_vec3d rodrigues(t_vec3d *v, t_vec3d *norm, float theta) {
    float c = cosf(theta);
    float s = sinf(theta);
    float dot = dot_vecs(norm, v);
    t_vec3d cross = cross_vecs(norm, v);

    t_vec3d rot;
    rot.x = v->x * c + cross.x * s + norm->x * dot * (1 - c);
    rot.y = v->y * c + cross.y * s + norm->y * dot * (1 - c);
    rot.z = v->z * c + cross.z * s + norm->z * dot * (1 - c);
    return rot;
}

t_vec3d to_local_space(t_vec3d *v, t_vec3d *norm) {
    t_vec3d z_axis = {0, 0, 1};
    // *norm = norm_vec(norm);

    float cos_theta = dot_vecs(norm, &z_axis);
    if (cos_theta > 0.0001f)
        return *v;
    if (cos_theta < -0.0001f) 
        return (t_vec3d){v->x, v->y, -v->z};

    float theta = acosf(cos_theta);
    t_vec3d axis = cross_vecs(norm, &z_axis);
    axis = norm_vec(&axis);

    return rodrigues(v, &axis, theta);
}

t_vec3d to_world_space(t_vec3d *v, t_vec3d *norm) {
    t_vec3d z_axis = {0, 0, 1};
    // *norm = norm_vec(norm);

    float cos_theta = dot_vecs(&z_axis, norm);
    if (cos_theta > 0.0001f)
        return *v;
    if (cos_theta < -0.0001f) 
        return (t_vec3d){v->x, v->y, -v->z};

    float theta = acosf(cos_theta);
    t_vec3d axis = cross_vecs(&z_axis, norm);
    axis = norm_vec(&axis);

    return rodrigues(v, &axis, theta);
}

t_hit *cylinder_hit(t_ray *ray, t_cylinder *cy)
{
	t_hit	*hit;

	t_vec3d dir;
	t_vec3d ori; 

	// *cy->norm = norm_vec(cy->norm);
	dir = to_local_space(&ray->dir, cy->norm);
	dir.z = 0;
	ori = to_local_space(&ray->ori, cy->norm);
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

	t_vec3d center = sub_vecs(&hit->position, cy->coord);
	float len = dot_vecs(&center, cy->norm);
	if (len < (-cy->height/2.0f) || len > (cy->height /2.0f))
	{
		free(hit);
		return NULL;
	}

    t_vec3d hit_local = vec_x_scalar(&dir, t);
    hit_local = add_vecs(&ori, &hit_local);

    // local normal
    t_vec3d normal_local = { hit_local.x, hit_local.y, 0 };
    normal_local = norm_vec(&normal_local);

    // world position
    t_vec3d world_hit = to_world_space(&hit_local, cy->norm);
    world_hit = add_vecs(&world_hit, cy->coord);

    // world normal
    t_vec3d world_normal = to_world_space(&normal_local, cy->norm);
    world_normal = norm_vec(&world_normal);

    hit->distance = t;
    hit->position = world_hit;
    hit->direction = world_normal;
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
