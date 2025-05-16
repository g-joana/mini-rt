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

    if (scene->lights)
        free(scene->lights);
    if (scene->spheres)
        free(scene->spheres);
    if (scene->planes)
        free(scene->planes);
    if (scene->cylinders)
        free(scene->cylinders);
}

