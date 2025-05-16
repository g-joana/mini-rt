#include "../includes/minirt.h"

t_camera    init_camera(int amount, int ambient)
{
    t_camera camera ;

    camera.coordinates[0] = 0;
    camera.coordinates[1] = 0;
    camera.coordinates[2] = 0;
    camera.normalized[0] = 0;
    camera.normalized[1] = 0;
    camera.normalized[2] = 0;
    camera.fov = 0;
    return (camera);
}

t_light    init_ambient(int amount)
{
    t_light ambient;

    ambient.ambient = 1;
    ambient.coordinates[0] = 0;
    ambient.coordinates[1] = 0;
    ambient.coordinates[2] = 0;
    ambient.brightness[0] = 0;
    ambient.brightness[1] = 0;
    ambient.brightness[2] = 0;
    ambient.rgb[0] = 0;
    ambient.rgb[1] = 0;
    ambient.rgb[2] = 0;
    return (ambient);
}

t_light    *init_lights(int amount)
{
    t_light *lights ;

    lights = malloc(sizeof(t_light) * amount);
    int i = 0;
    while (i < amount)
    {
        lights[i].ambient = 0;
        lights[i].coordinates[0] = 0;
        lights[i].coordinates[1] = 0;
        lights[i].coordinates[2] = 0;
        lights[i].brightness[0] = 0;
        lights[i].brightness[1] = 0;
        lights[i].brightness[2] = 0;
        lights[i].rgb[0] = 0;
        lights[i].rgb[1] = 0;
        lights[i].rgb[2] = 0;
    }
    return (lights);
}

t_plane    *init_planes(int amount)
{
    t_plane *planes ;

    planes = malloc(sizeof(t_plane) * amount);
    int i = 0;
    while (i < amount)
    {
        planes[i].coordinates[0] = 0;
        planes[i].coordinates[1] = 0;
        planes[i].coordinates[2] = 0;
        planes[i].normalized[0] = 0;
        planes[i].normalized[1] = 0;
        planes[i].normalized[2] = 0;
        planes[i].rgb[0] = 0;
        planes[i].rgb[1] = 0;
        planes[i].rgb[2] = 0;
    }
    return (planes);
}

t_sphere    *init_spheres(int amount)
{
    t_sphere *spheres ;

    spheres = malloc(sizeof(t_sphere) * amount);
    int i = 0;
    while (i < amount)
    {
        spheres[i].coordinates[0] = 0;
        spheres[i].coordinates[1] = 0;
        spheres[i].coordinates[2] = 0;
        spheres[i].rgb[0] = 0;
        spheres[i].rgb[1] = 0;
        spheres[i].rgb[2] = 0;
        spheres[i].diameter = 0;
    }
    return (spheres);
}

t_cylinder    *init_cylinders(int amount)
{
    t_cylinder *cylinders ;

    cylinders = malloc(sizeof(t_cylinder) * amount);
    int i = 0;
    while (i < amount)
    {
        cylinders[i].coordinates[0] = 0;
        cylinders[i].coordinates[1] = 0;
        cylinders[i].coordinates[2] = 0;
        cylinders[i].normalized[0] = 0;
        cylinders[i].normalized[1] = 0;
        cylinders[i].normalized[2] = 0;
        cylinders[i].rgb[0] = 0;
        cylinders[i].rgb[1] = 0;
        cylinders[i].rgb[2] = 0;
        cylinders[i].diameter = 0;
        cylinders[i].height = 0;
    }
    return (cylinders);
}

t_scene malloc_scene(int *amount)
{
    t_scene scene;

    if (amount[A] != 1)
        exit_error(NULL, "scene needs 1 ambient light placed", 1);
    if (amount[C] != 1)
        exit_error(NULL, "scene needs 1 camera placed", 1);
    if (amount[L])
        scene.lights = init_lights(amount[L]);
    if (amount[PL])
        scene.planes = init_planes(amount[PL]);
    if (amount[SP])
        scene.spheres = init_spheres(amount[SP]);
    if (amount[CY])
        scene.cylinders = init_cylinders(amount[CY]);
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
    if (!id)
        exit_error(NULL, "empty file", 1);
    while (id)
    {
        if (ft_strncmp("A", id, 2) == 0)
            amount[A]++;
        else if (ft_strncmp("C", id, 2) == 0)
            amount[C]++;
        else if (ft_strncmp("L", id, 2) == 0)
            amount[L]++;
        else if (ft_strncmp("pl", id, 3) == 0)
            amount[PL]++;
        else if (ft_strncmp("sp", id, 3) == 0)
            amount[SP]++;
        else if (ft_strncmp("cy", id, 3) == 0)
            amount[CY]++;
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

    if (ft_strlen(ft_strstr(file, ".rt")) != 3)
        exit_error(NULL, "invalid file extension", 1);
    if (access(file, O_RDONLY) != 0)
        exit_error(NULL, "invalid file", 1);
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

