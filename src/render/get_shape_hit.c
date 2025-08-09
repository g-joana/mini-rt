/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape_hit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:39:42 by jgils             #+#    #+#             */
/*   Updated: 2025/08/09 17:39:43 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_hit	*plane_hit(t_ray *ray, t_plane *pl)
{
	t_hit	*hit;
	float	cos_angle;
	float	t;

	cos_angle = dot_vecs(&ray->dir, pl->norm);
	if (cos_angle < 0.0001f && cos_angle > -0.0001f)
		return (NULL);
	t = -dot_vecs(&ray->ori, pl->norm) / cos_angle;
	if (t < 0.0001f)
		return (NULL);
	hit = malloc(sizeof(t_hit));
	if (!hit)
		return (NULL);
	hit->distance = t;
	return (hit);
}

float	quadratic(t_ray *ray, float radius)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t;

	a = dot_vecs(&ray->dir, &ray->dir);
	b = 2.0f * dot_vecs(&ray->ori, &ray->dir);
	c = dot_vecs(&ray->ori, &ray->ori) - radius * radius;
	delta = b * b - 4.0f * a * c;
	if (delta < 0.0f)
		return (0);
	t = (-b - sqrtf(delta)) / (2.0f * a);
	if (t < 0.001f)
		t = (-b + sqrtf(delta)) / (2.0f * a);
	return (t);
}

t_hit	*sphere_hit(t_ray *ray, t_sphere *sp)
{
	t_hit	*hit;
	float	t;

	t = quadratic(ray, sp->diam / 2);
	if (t < 0.001f)
		return (NULL);
	hit = malloc(sizeof(t_hit));
	if (!hit)
		return (NULL);
	hit->distance = t;
	return (hit);
}

t_vec3d	get_ori(t_ray *global_ray, t_vec3d *shape_ori, t_vec3d *cam_ori)
{
	t_vec3d	ray_ori;

	if (global_ray->shadow == false)
		ray_ori = sub_vecs(cam_ori, shape_ori);
	else
		ray_ori = sub_vecs(&global_ray->ori, shape_ori);
	return (ray_ori);
}

t_hit	*get_shape_hit(t_ray *ray, t_scene *scene, int shape, int id)
{
	t_hit	*hit;
	t_ray	local;

	local = *ray;
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
	return (hit);
}
