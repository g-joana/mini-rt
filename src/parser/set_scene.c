/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:57:27 by nranna            #+#    #+#             */
/*   Updated: 2025/07/30 21:30:34 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// set = seta os valores no seu devido campo da struct
// cada elemento da cena tem sua propriedade, nesse arquivo setamos os elementos
//
// tratar erros: se nao houver input (properties[index]) chamar exit_error
// problemas: free da gnl

void    set_vec3d(char *str, t_vec3d *vec)
{
    int status;
    char *ref;
    
    ref = str;
    if (!ref)
        status = 1;
	vec->x = ref_atof(ref);
    if (!ref)
        status = 1;
	vec->y = ref_atof(ref);
    if (!ref)
        status = 1;
	vec->z = ref_atof(ref);
    if (status == 1)
        vec = NULL;
}

void	set_camera(char *line, t_scene *scene)
{
	char	**properties;

	properties = ft_split(line, ' ');
	if (!properties[1] || !properties[2] || !properties[3])
	{
		free(line);
		free(properties);
		free_gnl(scene->fd);
		exit_error(scene, "missing camera (C) settings", 1);
	}
	set_coordinates(properties[1], scene->cam.coord);
	set_normalization(properties[2], scene->cam.norm);
	set_fov(properties[3], &scene->cam.fov);
	free_split(properties);
	t_vec3d up_direction = {0.0f, 1.0f, 0.0f};
	if (fabs(dot_vecs(scene->cam.norm, &up_direction)) > 0.99f) {
		up_direction = (t_vec3d){0.0f, 0.0f, 1.0f};
	}
	t_vec3d temp = cross_vecs(scene->cam.norm, &up_direction);
	*scene->cam.foward = norm_vec(scene->cam.norm);
	*scene->cam.right = norm_vec(&temp);
	*scene->cam.up = cross_vecs(scene->cam.foward, scene->cam.right);
}

void	set_ambient(char *line, t_scene *scene)
{
	char	**properties;

	properties = ft_split(line, ' ');
	if (!properties[1] || !properties[2])
	{
		free(line);
		free(properties);
		free_gnl(scene->fd);
		exit_error(scene, "missing ambient light (A) settings", 1);
	}
	set_brightness(properties[1], &scene->amb_light.bright);
	set_rgb(properties[2], scene->amb_light.rgb);
	free_split(properties);
}

void	set_light(char *line, t_scene *scene)
{
	char	**properties;

	properties = ft_split(line, ' ');
	if (!properties[1] || !properties[2] || !properties[3])
	{
		free(line);
		free(properties);
		free_gnl(scene->fd);
		exit_error(scene, "missing light (L) settings", 1);
	}
	set_coordinates(properties[1], scene->light.coord);
	set_brightness(properties[2], &scene->light.bright);
	set_rgb(properties[3], scene->light.rgb);
	free_split(properties);
}
