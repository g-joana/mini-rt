/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magni_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:44:35 by nranna            #+#    #+#             */
/*   Updated: 2025/06/02 12:44:21 by jou              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trivec.h"

/* returns the magnitude of param vec */
double	magni_vec(const t_vec3d *vec)
{
	double	mod_v;

	mod_v = sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
	return (mod_v);
}
