/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:55:15 by nranna            #+#    #+#             */
/*   Updated: 2025/07/29 18:25:06 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vec3d *new_vec3d() {
    t_vec3d *new;

	new = malloc(sizeof(t_vec3d));
	new->x = 0;
	new->y = 0;
	new->z = 0;
    return new;
}

/* init = malloc and set values to 0
   setup = camera, light, ambient light
   (elements that can only be declared once have a capital letter)
*/
t_alight	init_ambient(void)
{
	t_alight	ambient;

	ambient.bright = 0;
	ambient.rgb = new_vec3d();
	return (ambient);
}

t_light	init_light(void)
{
	t_light	light;

	light.coord = new_vec3d();
	light.rgb = new_vec3d();
	light.bright = 0;
	return (light);
}

t_camera	init_camera(void)
{
	t_camera	cam;

	cam.fov = 0;
	cam.coord = new_vec3d();
	cam.norm = new_vec3d();
	cam.foward = new_vec3d();
	cam.right = new_vec3d();
	cam.up = new_vec3d();
	return (cam);
}
