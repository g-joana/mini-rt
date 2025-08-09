/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_properties.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:38:57 by jgils             #+#    #+#             */
/*   Updated: 2025/08/09 17:38:57 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	set_vec3d(char *str, t_vec3d **vec)
{
	char	**split;

	split = ft_split(str, ',');
	if (split_len(split) != 3 || !valid_vec(split))
		return (1);
	(*vec)->x = ft_atof(split[0]);
	(*vec)->y = ft_atof(split[1]);
	(*vec)->z = ft_atof(split[2]);
	free_split(split);
	return (0);
}

int	set_norm(char *str, t_vec3d **vec)
{
	if (set_vec3d(str, vec) == 1)
		return (1);
	if ((*vec)->x < -1.0000 || (*vec)->x > 1.0000)
		return (1);
	else if ((*vec)->y < -1.0000 || (*vec)->y > 1.0000)
		return (1);
	else if ((*vec)->z < -1.0000 || (*vec)->z > 1.0000)
		return (1);
    **vec = norm_vec(*vec);
	return (0);
}

int	set_rgb(char *str, t_vec3d **vec)
{
	if (set_vec3d(str, vec) == 1)
		return (1);
	if ((*vec)->x < 0 || (*vec)->x > 255)
		return (1);
	else if ((*vec)->y < 0 || (*vec)->y > 255)
		return (1);
	else if ((*vec)->z < 0 || (*vec)->z > 255)
		return (1);
	return (0);
}

int	set_bright(char *str, float *bright)
{
	if (!valid_float(str))
		return (1);
	*bright = ft_atof(str);
	if (*bright < 0.0 || *bright > 1.0)
		return (1);
	return (0);
}

int	set_fov(char *str, uint8_t *fov)
{
	if (!valid_float(str))
		return (1);
	*fov = ft_atoi(str);
	if (*fov > 180)
		return 1;
	return 0;
}
