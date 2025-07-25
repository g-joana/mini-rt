/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_shapes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:56:54 by nranna            #+#    #+#             */
/*   Updated: 2025/07/18 08:24:32 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/* init = malloc and set values to 0
   shapes = sphere, plane, cylinder */
t_plane	*init_planes(int amount)
{
	int		i;
	t_plane	*planes;

	i = 0;
	planes = malloc(sizeof(t_plane) * amount);
	while (i < amount)
	{
		planes[i].coord = malloc(sizeof(t_vec3d));
		planes[i].coord->x = 0;
		planes[i].coord->y = 0;
		planes[i].coord->z = 0;
		planes[i].norm = malloc(sizeof(t_vec3d));
		planes[i].norm->x = 0;
		planes[i].norm->y = 0;
		planes[i].norm->z = 0;
		planes[i].rgb = malloc(sizeof(t_vec3d));
		planes[i].rgb->x = 0;
		planes[i].rgb->y = 0;
		planes[i].rgb->z = 0;
		i++;
	}
	return (planes);
}

t_sphere	*init_spheres(int amount)
{
	int			i;
	t_sphere	*spheres;

	i = 0;
	spheres = malloc(sizeof(t_sphere) * amount);
	while (i < amount)
	{
		spheres[i].coord = malloc(sizeof(t_vec3d));
		spheres[i].coord->x = 0;
		spheres[i].coord->y = 0;
		spheres[i].coord->z = 0;
		spheres[i].rgb = malloc(sizeof(t_vec3d));
		spheres[i].rgb->x = 0;
		spheres[i].rgb->y = 0;
		spheres[i].rgb->z = 0;
		spheres[i].diam = 0;
		i++;
	}
	return (spheres);
}

t_cylinder	*init_cylinders(int amount)
{
	int			i;
	t_cylinder	*cylinders;

	i = 0;
	cylinders = malloc(sizeof(t_cylinder) * amount);
	while (i < amount)
	{
		cylinders[i].coord = malloc(sizeof(t_vec3d));
		cylinders[i].coord->x = 0;
		cylinders[i].coord->y = 0;
		cylinders[i].coord->z = 0;
		cylinders[i].norm = malloc(sizeof(t_vec3d));
		cylinders[i].norm->x = 0;
		cylinders[i].norm->y = 0;
		cylinders[i].norm->z = 0;
		cylinders[i].rgb = malloc(sizeof(t_vec3d));
		cylinders[i].rgb->x = 0;
		cylinders[i].rgb->y = 0;
		cylinders[i].rgb->z = 0;
		cylinders[i].diam = 0;
		cylinders[i].height = 0;
		i++;
	}
	return (cylinders);
}
