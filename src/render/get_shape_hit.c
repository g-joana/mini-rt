#include "../../includes/minirt.h"

t_hit *plane_hit(t_ray *ray, t_plane *pl)
{
	t_hit	*hit;
	float cos_angle = dot_vecs(&ray->dir, pl->norm);

	// if parallel, no hit
	if (cos_angle < 0.0001f && cos_angle > -0.0001f)
	    return NULL;

	float t = -dot_vecs(&ray->ori, pl->norm) / cos_angle;

	if (t < 0.0001f)
	    return NULL;

	hit = malloc(sizeof(t_hit));
	if (!hit)
	    return NULL;
	hit->distance = t;
	
	return hit;
}

float quadratic(t_ray *ray, float radius)
{
	float a = dot_vecs(&ray->dir, &ray->dir);
	float b = 2.0f * dot_vecs(&ray->ori, &ray->dir);
	float c = dot_vecs(&ray->ori, &ray->ori) - radius * radius;

    float delta = b * b - 4.0f * a * c;
	if (delta < 0.0f)
	    return 0;
	float t = (-b - sqrtf(delta)) / (2.0f * a);
	if (t < 0.001f)
	    t = (-b + sqrtf(delta)) / (2.0f * a);
	return t;
}

t_hit *sphere_hit(t_ray *ray, t_sphere *sp)
{
	t_hit	*hit;
    float t;

    t = quadratic(ray, sp->diam/2);
	if (t < 0.001f)
	    return NULL;
	hit = malloc(sizeof(t_hit));
	if (!hit)
	    return NULL;
	hit->distance = t;
	return hit;
}

float cy_quadratic(t_ray *ray, float radius, float *t)
{
	float a = dot_vecs(&ray->dir, &ray->dir);
	float b = 2.0f * dot_vecs(&ray->ori, &ray->dir);
	float c = dot_vecs(&ray->ori, &ray->ori) - radius * radius;

    float delta = b * b - 4.0f * a * c;
	if (delta < 0.0f)
	    return 0;
	t[1] = (-b - sqrtf(delta)) / (2.0f * a);
    t[2] = (-b + sqrtf(delta)) / (2.0f * a);
    t[0] = t[1];
	if (t[0] < 0.001f)
	    t[0] = t[2];
	return t[0];
}

t_ray get_cy_ray(t_ray *ray, t_cylinder *cy, float *proj)
{
    t_ray axis;
    t_ray local;

    axis.ori = vec_x_scalar(cy->norm, proj[0]);
    axis.dir = vec_x_scalar(cy->norm, proj[1]);
    local.ori = sub_vecs(&ray->ori, &axis.ori);
    local.dir = sub_vecs(&ray->dir, &axis.dir);
    return local;
}

int valid_t(float *proj, float t, float cy_height)
{
    float hit_axis_pos;

    hit_axis_pos = proj[0] + t * proj[1];
    if (hit_axis_pos < -cy_height/2.0f || hit_axis_pos > cy_height/2.0f)
        return 0;
    return 1;
}

t_hit *cylinder_hit(t_ray *ray, t_cylinder *cy)
{
    t_hit *hit;
    float hit_axis_pos;
    float proj[2];
    t_ray local;
    float t[3];
    
    proj[0] = dot_vecs(&ray->ori, cy->norm);
    proj[1] = dot_vecs(&ray->dir, cy->norm);
    local = get_cy_ray(ray, cy, proj);
    t[0] = cy_quadratic(&local, cy->diam/2, t);
    if (t[0] < 0.001f)
        return NULL;
    hit_axis_pos = proj[0] + t[0] * proj[1];
    if (hit_axis_pos < -cy->height/2.0f || hit_axis_pos > cy->height/2.0f)
    {
        if (t[0] == t[1] && t[2] > 0.001f)
            t[0] = t[2];
        else
            return NULL;
        if (!valid_t(proj, t[2], cy->height))
            return NULL;
    }
    hit = malloc(sizeof(t_hit));
    if (!hit)
        return NULL;
    hit->distance = t[0];
    hit->inside = 0;
    if (t[0] == t[2])
        hit->inside = 1;
    return hit;
}

t_vec3d get_ori(t_ray *global_ray, t_vec3d *shape_ori, t_vec3d *cam_ori)
{
	t_vec3d ray_ori;

    if (global_ray->shadow == false)
        ray_ori = sub_vecs(cam_ori, shape_ori);
    else
        ray_ori = sub_vecs(&global_ray->ori, shape_ori);
    return ray_ori;
}

t_hit *get_shape_hit(t_ray *ray, t_scene *scene, int shape, int id)
{
	t_hit *hit;
	t_ray local = *ray;

	if (shape == PL)
	{
        local.ori = get_ori(ray, scene->planes[id].coord, scene->cam.coord);
	    hit = plane_hit(&local, &scene->planes[id]);
	}
	else if (shape == SP)
	{
        local.ori = get_ori(ray, scene->spheres[id].coord, scene->cam.coord);
	    hit = sphere_hit(&local, &scene->spheres[id]);
	}
	else if (shape == CY)
	{
        local.ori = get_ori(ray, scene->cylinders[id].coord, scene->cam.coord);
	    hit = cylinder_hit(&local, &scene->cylinders[id]);
	}
	if (hit)
	{
	    hit->shape = shape;
	    hit->id = id;
	}
	return hit;
}
