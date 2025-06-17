/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:55:15 by nranna            #+#    #+#             */
/*   Updated: 2025/06/15 16:00:17 by nranna           ###   ########.fr       */
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
	ambient.rgb = malloc(sizeof(uint8_t) * 3);
	ambient.rgb[0] = 0;
	ambient.rgb[1] = 0;
	ambient.rgb[2] = 0;
	return (ambient);
}

t_light	init_light(void)
{
	t_light	light;

	light.coord = malloc(sizeof(t_vec3d));
	light.coord->x = 0;
	light.coord->y = 0;
	light.coord->z = 0;
	light.rgb = malloc(sizeof(uint8_t) * 3);
	light.rgb[0] = 0;
	light.rgb[1] = 0;
	light.rgb[2] = 0;
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
	return (cam);
}
