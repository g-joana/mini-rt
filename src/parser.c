#include "../includes/minirt.h"

t_scene malloc_scene(int *amount)
{
    t_scene scene;

    if (amount[A] != 1)
        exit_error(NULL, "scene needs 1 ambient light placed", 1);
    if (amount[C] != 1)
        exit_error(NULL, "scene needs 1 camera placed", 1);
    // scene.ambient_light = init_ambient();
    // scene.camera = init_camera();
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

char *get_first_word(char *str)
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
    return (word);
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

float round4(float value) {
    // val= 3.141592
    // * 10000 = 31415.92
    // + 0.5f (round & cast to int)
    // / 10000 = 3.1416
    return ((int)(value * 10000 + 0.5f)) / 10000.0f;
}

int	power(int base, int expoent)
{
	int	ret;

	ret = 1;
	while (expoent--)
		ret *= base;
	return (ret);
}

float   ft_atof(char *str)
{
    int i = 0;
    int count = 0;
    float ret = ft_atoi(str);
    while (str && str[i] && str[i] != '.')
        i++;
    if (str[i] && str[i] == '.')
    {
        i++;
        while (str[i+count] && ft_isdigit(str[i + count]))
            count++;
        if (count)
            ret += (float)ft_atoi(&str[i]) / power(10, count);
    }
    // ret = round4(ret);
    return(ret);
}

t_camera    get_camera_info(char *line)
{
    t_camera    camera;
    char **properties = ft_split(line, ' ');
    char **temp;

    return (camera);
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
    // char *id = get_first_word(line);
    // while (line)
    // {
    //     if (ft_strncmp("A", id, 2) == 0)
    //         scene.camera = get_camera_info(line);
    //     else if (ft_strncmp("C", id, 2) == 0)
    //         amount[C]++;
    //     else if (ft_strncmp("L", id, 2) == 0)
    //         amount[L]++;
    //     else if (ft_strncmp("pl", id, 3) == 0)
    //         amount[PL]++;
    //     else if (ft_strncmp("sp", id, 3) == 0)
    //         amount[SP]++;
    //     else if (ft_strncmp("cy", id, 3) == 0)
    //         amount[CY]++;
    //     free(line);
    //     line = get_next_line(fd);
    //     free(id);
    //     id = get_first_word(line);
    // }
    // free(line);
    // free(id);
    // close(fd);
    return (scene);
}

