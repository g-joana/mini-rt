#include "../includes/minirt.h"

char *get_first_word(char *str, bool free_str)
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
    if (free_str)
        free(str);
    return (word);
}

// contagem de elementos na cena. quantidade de cada um retornada em um ponteiro de 6 int
int *count_elements(char *file)
{
    int *amount;
    amount = malloc(sizeof(int) * 6);
    // mudar inicializacao
    amount[0] = 0;
    amount[1] = 0;
    amount[2] = 0;
    amount[3] = 0;
    amount[4] = 0;
    amount[5] = 0;
    int fd = open(file, O_RDONLY);
    char *id = get_first_word(get_next_line(fd), 1);
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
            free(amount);
            free(id);
            free_gnl(fd);
            exit_error(NULL, "invalid id", 1);
        }
        free(id);
        id = get_first_word(get_next_line(fd), 1);
    }
    free(id);
    close(fd);
    // ft_printf("camera: %i\n", amount[0]);
    // ft_printf("ambient light: %i\n", amount[1]);
    // ft_printf("lights: %i\n", amount[2]);
    // ft_printf("spheres: %i\n", amount[3]);
    // ft_printf("planes: %i\n", amount[4]);
    // ft_printf("cylinders: %i\n", amount[5]);
    return(amount);
}

// inicializa a cena = malloca e zera tudo
t_scene *init_scene(char *file)
{
    t_scene *scene;

    int *amount = count_elements(file);
    scene = malloc(sizeof(t_scene));
    scene->amount = amount;
    // printf("%i\n", scene->amount[0]);
    // printf("%i\n", scene->amount[1]);
    // printf("%i\n", scene->amount[2]);
    // printf("%i\n", scene->amount[3]);
    if (scene->amount[A] != 1)
        exit_error(NULL, "scene needs 1 ambient light placed", 1);
    if (scene->amount[C] != 1)
        exit_error(NULL, "scene needs 1 camera placed", 1);
    scene->ambient_light = init_ambient();
    scene->camera = init_camera();
    if (scene->amount[L])
        scene->lights = init_lights(scene->amount[L]);
    if (scene->amount[PL])
        scene->planes = init_planes(scene->amount[PL]);
    if (scene->amount[SP])
        scene->spheres = init_spheres(scene->amount[SP]);
    if (scene->amount[CY])
        scene->cylinders = init_cylinders(scene->amount[CY]);
    return (scene);
}

// retorna um t_scene mallocado e preenchido
t_scene    *parse(char *file) {
    t_scene *scene;
    int count[6] = {0,0,0,0,0,0};

    if (ft_strlen(ft_strstr(file, ".rt")) != 3)
        exit_error(NULL, "invalid file format", 1);
    if (access(file, O_RDONLY) != 0)
        exit_error(NULL, "invalid file", 1);
    scene = init_scene(file);
    scene->fd = open(file, O_RDONLY);
    char *line = get_next_line(scene->fd);
    char *id = get_first_word(line, 0);
    while (line)
    {
        if (ft_strncmp("A", id, 2) == 0)
            set_ambient(line, scene);
        else if (ft_strncmp("C", id, 2) == 0)
            set_camera(line, scene);
        else if (ft_strncmp("L", id, 2) == 0)
            set_light(line, scene, count[L]++);
        else if (ft_strncmp("pl", id, 3) == 0)
            set_plane(line, scene, count[PL]++);
        else if (ft_strncmp("sp", id, 3) == 0)
            set_sphere(line, scene, count[SP]++);
        else if (ft_strncmp("cy", id, 3) == 0)
            set_cylinder(line, scene, count[CY]++);
        free(line);
        line = get_next_line(scene->fd);
        free(id);
        id = get_first_word(line, 0);
    }
    free(line);
    free(id);
    close(scene->fd);
    return (scene);
}

