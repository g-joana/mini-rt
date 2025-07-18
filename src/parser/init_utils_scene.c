/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:55:15 by nranna            #+#    #+#             */
/*   Updated: 2025/07/18 08:34:05 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/* init = malloc and set values to 0
   setup = camera, light, ambient light
   (elements that can only be declared once have a capital letter)
*/
t_alight	init_ambient(void)
{
	t_alight	ambient;

	ambient.bright = 0;
	ambient.rgb = malloc(sizeof(t_vec3d));
	ambient.rgb->x = 0;
	ambient.rgb->y = 0;
	ambient.rgb->z = 0;
	return (ambient);
}

t_light	init_light(void)
{
	t_light	light;

	light.coord = malloc(sizeof(t_vec3d));
	light.coord->x = 0;
	light.coord->y = 0;
	light.coord->z = 0;
	light.rgb = malloc(sizeof(t_vec3d));
	light.rgb->x = 0;
	light.rgb->y = 0;
	light.rgb->z = 0;
	light.bright = 0;
	return (light);
}

t_camera	init_camera(void)
{
	t_camera	cam;

	cam.coord = malloc(sizeof(t_vec3d));
	cam.coord->x = 0;
	cam.coord->y = 0;
	cam.coord->z = 0;
	cam.norm = malloc(sizeof(t_vec3d));
	cam.norm->x = 0;
	cam.norm->y = 0;
	cam.norm->z = 0;
	cam.fov = 0;
	cam.foward = malloc(sizeof(t_vec3d));
	cam.foward->x = 0;
	cam.foward->y = 0;
	cam.foward->z = 0;
	cam.right = malloc(sizeof(t_vec3d));
	cam.right->x = 0;
	cam.right->y = 0;
	cam.right->z = 0;
	cam.up = malloc(sizeof(t_vec3d));
	cam.up->x = 0;
	cam.up->y = 0;
	cam.up->z = 0;
	return (cam);
}
