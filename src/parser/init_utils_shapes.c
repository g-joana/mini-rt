/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_shapes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:56:54 by nranna            #+#    #+#             */
/*   Updated: 2025/07/29 18:28:23 by jgils            ###   ########.fr       */
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
		planes[i].coord = new_vec3d();
		planes[i].norm = new_vec3d();
		planes[i].rgb = new_vec3d();
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
		spheres[i].coord = new_vec3d();
		spheres[i].rgb = new_vec3d();
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
		cylinders[i].coord = new_vec3d();
		cylinders[i].norm = new_vec3d();
		cylinders[i].rgb = new_vec3d();
		cylinders[i].diam = 0;
		cylinders[i].height = 0;
		i++;
	}
	return (cylinders);
}
