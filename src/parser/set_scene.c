/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:38:59 by jgils             #+#    #+#             */
/*   Updated: 2025/08/09 17:38:59 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	set_camera(char **split, t_scene *scene)
{
	int		ret;
	t_vec3d	up_direction;
	t_vec3d	temp;

	ret = 0;
	if (split_len(split) < 4)
		exit_set(split, scene, "missing camera (C) settings");
	ret += set_vec3d(split[1], &scene->cam.coord);
	ret += set_vec3d(split[2], &scene->cam.norm);
	*scene->cam.norm = norm_vec(scene->cam.norm);
	ret += set_fov(split[3], &scene->cam.fov);
	if (ret != 0)
		exit_set(split, scene, "invalid camera (C) settings");
    up_direction = (t_vec3d){0.0f, 1.0f, 0.0f};
	if (fabs(dot_vecs(scene->cam.norm, &up_direction)) > 0.99f)
		up_direction = (t_vec3d){0.0f, 0.0f, 1.0f};
	temp = cross_vecs(scene->cam.norm, &up_direction);
	*scene->cam.foward = norm_vec(scene->cam.norm);
	*scene->cam.right = norm_vec(&temp);
	*scene->cam.up = cross_vecs(scene->cam.foward, scene->cam.right);
}

void	set_ambient(char **split, t_scene *scene)
{
	int	ret;

	ret = 0;
	if (split_len(split) < 3)
		exit_set(split, scene, "missing ambient light (A) settings");
	ret += set_bright(split[1], &scene->amb_light.bright);
	ret += set_rgb(split[2], &scene->amb_light.rgb);
	if (ret != 0)
		exit_set(split, scene, "invalid ambient light (A) settings");
}

void	set_light(char **split, t_scene *scene)
{
	int	ret;

	ret = 0;
	if (split_len(split) < 4)
		exit_set(split, scene, "missing light (L) settings");
	ret += set_vec3d(split[1], &scene->light.coord);
	ret += set_bright(split[2], &scene->light.bright);
	ret += set_rgb(split[3], &scene->light.rgb);
	if (ret != 0)
		exit_set(split, scene, "invalid light (L) settings");
}
