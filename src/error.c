#include "../includes/minirt.h"

void exit_error(t_scene* scene, char *msg, int ret)
{
    if (scene != NULL)
        free_scene(scene);
    ft_putstr_fd("Error: ", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
    exit(ret);
}

void exit_set(char **split, t_scene *scene, char *msg)
{
    free_split(split);
    free_gnl(scene->fd);
    exit_error(scene, msg, 1);
}
