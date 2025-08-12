/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trivec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:56:31 by nranna            #+#    #+#             */
/*   Updated: 2025/08/09 19:55:18 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIVEC_H
# define TRIVEC_H

# include <math.h>

typedef struct s_vec3d
{
	float	x;
	float	y;
	float	z;
}			t_vec3d;

t_vec3d		add_vecs(const t_vec3d *xyz_a, const t_vec3d *xyz_b);
t_vec3d		sub_vecs(const t_vec3d *xyz_a, const t_vec3d *xyz_b);
t_vec3d		norm_vec(const t_vec3d *vec);
t_vec3d		vec_x_scalar(const t_vec3d *vec, double scalar);
double		magni_vec(const t_vec3d *vec);
double		dot_vecs(const t_vec3d *xyz_a, const t_vec3d *xyz_b);
t_vec3d		cross_vecs(t_vec3d *a, t_vec3d *b);
#endif
