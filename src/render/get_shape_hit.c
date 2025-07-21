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
	return hit;
}

t_hit *cylinder_hit(t_ray *ray, t_cylinder *cy)
{
    t_hit *hit;
    
    t_vec3d local_origin = ray->ori;
    t_vec3d local_dir = ray->dir;
    
    float proj_origin = dot_vecs(&local_origin, cy->norm);
    float proj_dir = dot_vecs(&local_dir, cy->norm);
    
    t_vec3d axis_ori = vec_x_scalar(cy->norm, proj_origin);
    t_vec3d axis_dir = vec_x_scalar(cy->norm, proj_dir);
    
    t_vec3d ori = sub_vecs(&local_origin, &axis_ori);
    t_vec3d dir = sub_vecs(&local_dir, &axis_dir);
    
    float r = cy->diam / 2.0f;
    float a = dot_vecs(&dir, &dir);
    float b = 2.0f * dot_vecs(&ori, &dir);
    float c = dot_vecs(&ori, &ori) - r * r;
    
    float delta = b * b - 4.0f * a * c;
    if (delta < 0.0f)
        return NULL;
        
    float t = (-b - sqrtf(delta)) / (2.0f * a);
    // float t2 = (-b + sqrtf(delta)) / (2.0f * a);
    
    if (t < 0.001f)
        return NULL;
    
    float hit_axis_pos = proj_origin + t * proj_dir;
    if (hit_axis_pos < -cy->height/2.0f || hit_axis_pos > cy->height/2.0f)
            return NULL;
    
    hit = malloc(sizeof(t_hit));
    if (!hit)
        return NULL;
    hit->distance = t;
    return hit;
}

t_hit *get_shape_hit(t_ray *ray, t_scene *scene, int shape, int id)
{
	t_hit *hit;
	t_ray local_ray = *ray;

	if (shape == PL)
	{
		return NULL;
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
