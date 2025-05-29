/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_vecs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:19:50 by nranna            #+#    #+#             */
/*   Updated: 2025/05/28 20:32:58 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trivec.h"

t_vec3d	add_vecs(const t_vec3d *xyz_a, const t_vec3d *xyz_b)
{
	t_vec3d	c;

	c.x = xyz_a->x + xyz_b->x;
	c.y = xyz_a->y + xyz_b->y;
	c.z = xyz_a->z + xyz_b->z;
	return (c);
}
