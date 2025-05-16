#include "../includes/minirt.h"
#include <stdlib.h>

void exit_error(t_scene* scene, char *msg, int ret)
{
    if (scene != NULL)
        free_scene(scene);
    ft_putstr_fd("Error: ", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
    exit(ret);
}

t_scene malloc_scene(int *amount)
{
    t_scene scene;

    if (amount[0] != 1)
        exit_error(NULL, "scene needs 1 camera placed", 1);
    if (amount[1] != 1)
        exit_error(NULL, "scene needs 1 ambient light placed", 1);
    if (amount[2])
        scene.lights = malloc(sizeof(t_light) * amount[2]);
    if (amount[3])
        scene.spheres = malloc(sizeof(t_sphere) * amount[3]);
    if (amount[4])
        scene.planes = malloc(sizeof(t_plane) * amount[4]);
    if (amount[5])
        scene.cylinders = malloc(sizeof(t_cylinder) * amount[5]);
    return (scene);
}

t_scene init_scene(char *file)
{
    int amount[6] = {0, 0, 0, 0, 0, 0};
    int fd = open(file, O_RDONLY);
    char *line = get_next_line(fd);
    while (line)
    {
        if (line[0] == '\n')
            continue ;
        else if (ft_strncmp("A ", line, 2) == 0)
            amount[0]++;
        else if (ft_strncmp("C ", line, 2) == 0)
            amount[1]++;
        else if (ft_strncmp("L ", line, 2) == 0)
            amount[2]++;
        else if (ft_strncmp("sp ", line, 3) == 0)
            amount[3]++;
        else if (ft_strncmp("pl ", line, 3) == 0)
            amount[4]++;
        else if (ft_strncmp("cy ", line, 3) == 0)
            amount[5]++;
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    close(fd);
    return(malloc_scene(amount));
}

t_scene    parse(char *file) {
    t_scene scene;

    scene = init_scene(file);
    return (scene);
    // int fd = open(file, O_RDONLY);
    // char *line = get_next_line(fd);
    // while (line)
    // {
    // }
    // close(fd);
}

