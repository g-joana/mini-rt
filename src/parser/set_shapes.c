/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:52:27 by nranna            #+#    #+#             */
/*   Updated: 2025/06/13 17:56:32 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	set_cylinder(char *line, t_scene *scene, int i)
{
	char	**properties;

	properties = ft_split(line, ' ');
	if (!properties[1] || !properties[2] || !properties[3] || !properties[4]
		|| !properties[5])
	{
		free(line);
		free(properties);
		free_gnl(scene->fd);
		exit_error(scene, "missing cylinder (cy) settings", 1);
	}
	set_coordinates(properties[1], scene->cylinders[i].coord);
	set_normalization(properties[2], scene->cylinders[i].norm);
	set_diameter(properties[3], &scene->cylinders[i].diam);
	set_height(properties[4], &scene->cylinders[i].height);
	set_rgb(properties[5], scene->cylinders[i].rgb);
	free_split(properties);
}

void	set_sphere(char *line, t_scene *scene, int i)
{
	char	**properties;

	properties = ft_split(line, ' ');
	if (!properties[1] || !properties[2] || !properties[3])
	{
		free(line);
		free(properties);
		free_gnl(scene->fd);
		exit_error(scene, "missing sphere (sp) settings", 1);
	}
	set_coordinates(properties[1], scene->spheres[i].coord);
	set_diameter(properties[2], &scene->spheres[i].diam);
	set_rgb(properties[3], scene->spheres[i].rgb);
	free_split(properties);
}

void	set_plane(char *line, t_scene *scene, int i)
{
	char	**properties;

	properties = ft_split(line, ' ');
	if (!properties[1] || !properties[2] || !properties[3])
	{
		free(line);
		free(properties);
		free_gnl(scene->fd);
		exit_error(scene, "missing plane (pl) settings", 1);
	}
	set_coordinates(properties[1], scene->planes[i].coord);
	set_normalization(properties[2], scene->planes[i].norm);
	set_rgb(properties[3], scene->planes[i].rgb);
	free_split(properties);
}

// range: positive (measure)
void	set_diameter(char *str, float *diam)
{
	char	**values;

	values = ft_split(str, ',');
	*diam = ft_atof(values[0]);
	free_split(values);
}

// range: positive (measure)
void	set_height(char *str, float *height)
{
	char	**values;

	values = ft_split(str, ',');
	*height = ft_atof(values[0]);
	free_split(values);
}
