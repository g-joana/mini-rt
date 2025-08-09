/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:39:19 by jgils             #+#    #+#             */
/*   Updated: 2025/08/09 17:39:19 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	free_gnl(int fd)
{
	char	*buf;

	buf = get_next_line(fd);
	while (buf != NULL)
	{
		free(buf);
		buf = get_next_line(fd);
	}
	close(fd);
}

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	key_hook(int key, t_scene *scene)
{
	if (key == 65307)
	{
		mlx_destroy_image(scene->mlx, scene->img.img);
		mlx_destroy_window(scene->mlx, scene->mlx_win);
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
		free_scene(scene);
		exit(0);
	}
	return (1);
}

int	mouse_hook(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->img.img);
	mlx_destroy_window(scene->mlx, scene->mlx_win);
	mlx_destroy_display(scene->mlx);
	free(scene->mlx);
	free_scene(scene);
	exit(0);
	return (1);
}
