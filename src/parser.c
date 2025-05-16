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

t_scene malloc_scene(int *amount)
{
    t_scene scene;

    if (amount[0] != 1)
        exit_error(NULL, "scene needs 1 ambient light placed", 1);
    if (amount[1] != 1)
        exit_error(NULL, "scene needs 1 camera placed", 1);
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

char *extract_first_word(char *str)
{
    int i = 0;
    int count = 0;

    if (str == NULL)
        return (NULL);
    while (str && str[i] == ' ')
        i++;
    while (str && str[i + count] != '\0' && str[i + count] != ' ')
        count++;
    char *word = malloc((count + 1) * sizeof(char));
    count = 0;
    while (str && str[i + count] != '\0' && str[i + count] != ' ')
    {
        word[count] = str[i + count];
        count++;
    }
    word[count] = '\0';
    free(str);
    return (word);
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

t_scene init_scene(char *file)
{
    int amount[6] = {0, 0, 0, 0, 0, 0};
    int fd = open(file, O_RDONLY);
    char *id = extract_first_word(get_next_line(fd));
    while (id)
    {
        if (ft_strncmp("A", id, 2) == 0)
            amount[0]++;
        else if (ft_strncmp("C", id, 2) == 0)
            amount[1]++;
        else if (ft_strncmp("L", id, 2) == 0)
            amount[2]++;
        else if (ft_strncmp("sp", id, 3) == 0)
            amount[3]++;
        else if (ft_strncmp("pl", id, 3) == 0)
            amount[4]++;
        else if (ft_strncmp("cy", id, 3) == 0)
            amount[5]++;
        else if (id[0] != '\n')
        {
            free(id);
            free_gnl(fd);
            exit_error(NULL, "invalid id", 1);
        }
        free(id);
        id = extract_first_word(get_next_line(fd));
    }
    free(id);
    close(fd);
    // ft_printf("camera: %i\n", amount[0]);
    // ft_printf("ambient light: %i\n", amount[1]);
    // ft_printf("lights: %i\n", amount[2]);
    // ft_printf("spheres: %i\n", amount[3]);
    // ft_printf("planes: %i\n", amount[4]);
    // ft_printf("cylinders: %i\n", amount[5]);
    return(malloc_scene(amount));
}

t_scene    parse(char *file) {
    t_scene scene;

    scene = init_scene(file);
    // scene.ambient_light = get_amblight_info(file);
    // scene.camera = get_camera_info(file);
    // scene.lights = get_light_info(file);

    // int fd = open(file, O_RDONLY);
    // char *line = get_next_line(fd);
    // while (line)
    // {
    // }
    // close(fd);
    return (scene);
}

