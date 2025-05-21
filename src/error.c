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
