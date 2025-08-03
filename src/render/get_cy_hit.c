#include "../../includes/minirt.h"

static float cy_quadratic(t_ray *ray, float radius, float *t)
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

static t_ray get_cy_ray(t_ray *ray, t_cylinder *cy, float *proj)
{
    t_ray axis;
    t_ray local;

    axis.ori = vec_x_scalar(cy->norm, proj[0]);
    axis.dir = vec_x_scalar(cy->norm, proj[1]);
    local.ori = sub_vecs(&ray->ori, &axis.ori);
    local.dir = sub_vecs(&ray->dir, &axis.dir);
    return local;
}

static int valid_t(float *proj, float t, float cy_height)
{
    float hit_axis_pos;

    hit_axis_pos = proj[0] + t * proj[1];
    if (hit_axis_pos < -cy_height/2.0f || hit_axis_pos > cy_height/2.0f)
        return 0;
    return 1;
}

static t_hit *cy_hit(float *t)
{
    t_hit *hit;

    hit = malloc(sizeof(t_hit));
    if (!hit)
        return NULL;
    hit->distance = t[0];
    hit->inside = 0;
    if (t[0] == t[2])
        hit->inside = 1;
    return (hit);
}

t_hit *cylinder_hit(t_ray *ray, t_cylinder *cy)
{
    t_hit *hit;
    float proj[2];
    t_ray local;
    float t[3];
    
    proj[0] = dot_vecs(&ray->ori, cy->norm);
    proj[1] = dot_vecs(&ray->dir, cy->norm);
    local = get_cy_ray(ray, cy, proj);
    t[0] = cy_quadratic(&local, cy->diam/2, t);
    if (t[0] < 0.001f)
        return NULL;
    if (!valid_t(proj, t[0], cy->height))
    {
        if (t[0] != t[1] || t[2] <= 0.001f)
            return NULL;
        t[0] = t[2];
        if (!valid_t(proj, t[2], cy->height))
            return NULL;
    }
    hit = cy_hit(t);
    return hit;
}
