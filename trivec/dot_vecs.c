/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_vecs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:02:36 by nranna            #+#    #+#             */
/*   Updated: 2025/06/02 12:44:54 by jou              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trivec.h"

/* returns the angle between vec1 and vec2 */
double	dot_vecs(const t_vec3d *xyz_a, const t_vec3d *xyz_b)
{
	double	a_x_b;

	a_x_b = (xyz_a->x * xyz_b->x) + (xyz_a->y * xyz_b->y)
		+ (xyz_a->z * xyz_b->z);
	return (a_x_b);
}
