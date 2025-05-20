#include "../includes/minirt.h"

void free_scene(t_scene *scene)
{
    int count = 0;
    // if (scene->lights)
    //     ft_putstr_fd("free lights\n", 1);
    // if (scene->spheres)
    //     ft_putstr_fd("free shperes\n", 1);
    // if (scene->planes)
    //     ft_putstr_fd("free planes\n", 1);
    // if (scene->cylinders)
    //     ft_putstr_fd("free cylinders\n", 1);


    free(scene->camera.coordinates);
    free(scene->camera.normalized);
    free(scene->ambient_light.brightness);
    free(scene->ambient_light.rgb);
    // dar free nas propriedades de cada um!!!
    if (scene->lights)
    {
        count = 0;
        while (count < scene->amount[L])
        {
            free(scene->lights[count].coordinates);
            free(scene->lights[count].brightness);
            free(scene->lights[count].rgb);
            count++;
        }
        free(scene->lights);
    }
    if (scene->spheres)
    {
        count = 0;
        while (count < scene->amount[SP])
        {
            free(scene->spheres[count].coordinates);
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
            free(scene->planes[count].coordinates);
            free(scene->planes[count].normalized);
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
            free(scene->cylinders[count].coordinates);
            free(scene->cylinders[count].normalized);
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
