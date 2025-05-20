#include "../includes/minirt.h"

void free_scene(t_scene *scene)
{
    // if (scene->lights)
    //     ft_putstr_fd("free lights\n", 1);
    // if (scene->spheres)
    //     ft_putstr_fd("free shperes\n", 1);
    // if (scene->planes)
    //     ft_putstr_fd("free planes\n", 1);
    // if (scene->cylinders)
    //     ft_putstr_fd("free cylinders\n", 1);


    // dar free nas propriedades de cada um!!!
    if (scene->lights)
        free(scene->lights);
    if (scene->spheres)
        free(scene->spheres);
    if (scene->planes)
        free(scene->planes);
    if (scene->cylinders)
        free(scene->cylinders);
    free(scene->amount);
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
