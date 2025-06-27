#include "../includes/minirt.h"

void free_scene(t_scene *scene)
{
    int count = 0;
    free(scene->cam.coord);
    free(scene->cam.norm);
    free(scene->cam.foward);
    free(scene->cam.up);
    free(scene->cam.right);
    free(scene->amb_light.rgb);
    free(scene->light.coord);
    free(scene->light.rgb);
    if (scene->spheres)
    {
        count = 0;
        while (count < scene->amount[SP])
        {
            free(scene->spheres[count].coord);
            free(scene->spheres[count].rgb);
            count++;
        }
        free(scene->spheres);
    }
    if (scene->planes)
    {
        count = 0;
        while (count < scene->amount[PL])
        {
            free(scene->planes[count].coord);
            free(scene->planes[count].norm);
            free(scene->planes[count].rgb);
            count++;
        }
        free(scene->planes);
    }
    if (scene->cylinders)
    {
        count = 0;
        while (count < scene->amount[CY])
        {
            free(scene->cylinders[count].coord);
            free(scene->cylinders[count].norm);
            free(scene->cylinders[count].rgb);
            count++;
        }
        free(scene->cylinders);
    }
    free(scene->amount);
    free(scene);
}

void free_gnl(int fd)
{
    char *buf = get_next_line(fd);
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
    free_scene(scene);
	exit(0);
	return (1);
}
