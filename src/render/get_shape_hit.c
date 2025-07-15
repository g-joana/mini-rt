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

	return NULL;
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
