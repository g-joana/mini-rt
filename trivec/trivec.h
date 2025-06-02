/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trivec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:56:31 by nranna            #+#    #+#             */
/*   Updated: 2025/05/28 21:51:33 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIVEC_H
# define TRIVEC_H

//I don't think it's a good idea to include minirt.h here because we'll only
//need a few math funtions, just math.h should be good

# include <math.h>

typedef struct s_vec3d
{
	double		x;
	double		y;
	double		z;
}				t_vec3d;

//I'm worried about performance, that's why I'm passing it by reference
//sorry for the pointers and future complication on our code... teehe..
t_vec3d	add_vecs(const t_vec3d *xyz_a, const t_vec3d *xyz_b);
t_vec3d	sub_vecs(const t_vec3d *xyz_a, const t_vec3d *xyz_b);
t_vec3d	norm_vec(const t_vec3d *vec);
t_vec3d vec_x_scalar(const t_vec3d *vec, double scalar);
double	magni_vec(const t_vec3d *vec);
double	dot_vecs(const t_vec3d *xyz_a, const t_vec3d *xyz_b);

#endif
