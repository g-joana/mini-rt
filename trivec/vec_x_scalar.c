/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_x_scalar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:37:48 by nranna            #+#    #+#             */
/*   Updated: 2025/05/28 21:48:46 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trivec.h"

t_vec3d vec_x_scalar(const t_vec3d *vec, double scalar)
{
	t_vec3d	svec;

	svec.x = vec->x * scalar;
	svec.y = vec->y * scalar;
	svec.z = vec->z * scalar;
	return (svec);
}
