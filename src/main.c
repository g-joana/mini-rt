/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:52:12 by nranna            #+#    #+#             */
/*   Updated: 2025/06/15 16:50:37 by jou              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	start_mlx(t_scene *scene);

//check leaks
int main(int argc, char **argv)
{
    t_scene	*scene;

    if (argc != 2)
		exit_error(NULL, "(ERROR) no input file: ./minirt [file.rt]", 1);
	scene = parser(argv[1]);
	print_scene(scene);
	start_mlx(scene);
	mlx_loop_hook(scene->mlx, render, scene); //change 2nd param to learn render
	mlx_loop(scene->mlx);
	free_scene(scene);
	return (0);
}

void	start_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	scene->mlx_win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "minirt");
	scene->img.img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	scene->img.addr = mlx_get_data_addr(scene->img.img, &scene->img.bits_per_pixel,
			&scene->img.line_len, &scene->img.endian);
	mlx_key_hook(scene->mlx_win, key_hook, scene);
	// mlx_hook(scene->mlx_win, 17, 1L << 17, mouse_hook, scene);
}
