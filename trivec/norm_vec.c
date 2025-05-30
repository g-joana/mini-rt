/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:10:34 by nranna            #+#    #+#             */
/*   Updated: 2025/05/28 21:26:40 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trivec.h"

t_vec3d	norm_vec(const t_vec3d *vec)
{
	t_vec3d versor;
	double	mod_vec;

	if (vec->x == 0 && vec->y == 0 && vec->z == 0)
	{
		versor.x = 0;
		versor.y = 0;
		versor.z = 0;
		return (versor);
	}
	mod_vec = magni_vec(vec);
	if (mod_vec <= 1e-9)
	{
		versor.x = 0;
		versor.y = 0;
		versor.z = 0;
		return (versor);
	}
	versor.x = vec->x / mod_vec;
	versor.y = vec->y / mod_vec;
	versor.z = vec->z / mod_vec;
	return (versor);
}
