/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_properties.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:50:24 by nranna            #+#    #+#             */
/*   Updated: 2025/07/29 19:25:28 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/* set = set values on it's corresponding structs
 each element on scene has it's on properties and in this file we set them.
*/

void    set_vec3d(char *str, t_vec3d *vec)
{
    char *ref;

	vec->x = ref_atof(ref);
	vec->y = ref_atof(ref);
	vec->z = ref_atof(ref);
}

// range: fe
void	set_coordinates(char *str, t_vec3d *coord)
{
	char	**values;

	values = ft_split(str, ',');
    coord->x = ft_atof(values[0]);
    coord->y = ft_atof(values[1]);
    coord->z = ft_atof(values[2]);
	free_split(values);
}

// range: -1 ~ 1
void	set_normalization(char *str, t_vec3d *norm)
{
	char	**values;

	values = ft_split(str, ',');
	norm->x = ft_atof(values[0]);
	norm->y = ft_atof(values[1]);
	norm->z = ft_atof(values[2]);
	free_split(values);
    *norm = norm_vec(norm);
}

// range: 0.0 ~ 1.0
void	set_brightness(char *str, float *bright)
{
	char	**values;

	values = ft_split(str, ',');
	*bright = ft_atof(values[0]);
	free_split(values);
}

// range: 0 ~ 255
void	set_rgb(char *str, t_vec3d *rgb)
{
	char	**values;

	values = ft_split(str, ',');
	rgb->x = ft_atoi(values[0]);
	rgb->y = ft_atoi(values[1]);
	rgb->z = ft_atoi(values[2]);
	free_split(values);
}

// range: 0 ~ 180
void	set_fov(char *str, uint8_t *fov)
{
	char	**values;

	values = ft_split(str, ',');
	*fov = ft_atoi(values[0]);
	free_split(values);
}
