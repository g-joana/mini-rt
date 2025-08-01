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

t_hit *cylinder_hit(t_ray *ray, t_cylinder *cy)
{
    t_hit *hit;
    
    float proj_origin = dot_vecs(&ray->ori, cy->norm);
    float proj_dir = dot_vecs(&ray->dir, cy->norm);
    
    t_vec3d axis_ori = vec_x_scalar(cy->norm, proj_origin);
    t_vec3d axis_dir = vec_x_scalar(cy->norm, proj_dir);
    
    t_vec3d ori = sub_vecs(&ray->ori, &axis_ori);
    t_vec3d dir = sub_vecs(&ray->dir, &axis_dir);
    
    float r = cy->diam / 2.0f;
    float a = dot_vecs(&dir, &dir);
    float b = 2.0f * dot_vecs(&ori, &dir);
    float c = dot_vecs(&ori, &ori) - r * r;
    
    float delta = b * b - 4.0f * a * c;
    if (delta < 0.0f)
        return NULL;
    float t1 = (-b - sqrtf(delta)) / (2.0f * a);
    float t2 = (-b + sqrtf(delta)) / (2.0f * a);

    float t = t1;
    if (t < 0.001f)
	t = t2;
    if (t < 0.001f)
	return NULL;


    float hit_axis_pos = proj_origin + t * proj_dir;
    if (hit_axis_pos < -cy->height/2.0f || hit_axis_pos > cy->height/2.0f)
    {
	if (t == t1)
	    t = t2;
	if (t < 0.001f)
	    return NULL;

	hit_axis_pos = proj_origin + t * proj_dir;
	if (hit_axis_pos < -cy->height/2.0f || hit_axis_pos > cy->height/2.0f)
	    return NULL;
    }
    
    hit = malloc(sizeof(t_hit));
    if (!hit)
        return NULL;
    hit->distance = t;
    if (t == t2)
	hit->inside = 1;
    else
	hit->inside = 0;
    return hit;
}

t_hit *get_shape_hit(t_ray *ray, t_scene *scene, int shape, int id)
{
	t_hit *hit;
	t_ray local_ray = *ray;

	if (shape == PL)
	{
	    if (ray->shadow == false)
		local_ray.ori = sub_vecs(scene->cam.coord, scene->planes[id].coord);
	    else
		local_ray.ori = sub_vecs(&ray->ori, scene->planes[id].coord);
	    hit = plane_hit(&local_ray, &scene->planes[id]);
	}
	else if (shape == SP)
	{
	    if (ray->shadow == false)
		local_ray.ori = sub_vecs(scene->cam.coord, scene->spheres[id].coord);
	    else
		local_ray.ori = sub_vecs(&ray->ori, scene->spheres[id].coord);
	    hit = sphere_hit(&local_ray, &scene->spheres[id]);
	}
	else if (shape == CY)
	{
	    if (ray->shadow == false)
		local_ray.ori = sub_vecs(scene->cam.coord, scene->cylinders[id].coord);
	    else
		local_ray.ori = sub_vecs(&ray->ori, scene->cylinders[id].coord);
	    hit = cylinder_hit(&local_ray, &scene->cylinders[id]);
	}
	if (hit)
	{
	    hit->shape = shape;
	    hit->id = id;
	}
	return hit;
}
