#include "../includes/minirt.h"
// set = seta os valores no seu devido campo da struct
// cada elemento da cena tem sua propriedade, nesse arquivo setamos os elementos
//
// tratar erros: se nao houver input (properties[index]) chamar exit_error
// problemas: free da gnl

void    set_camera(char *line, t_scene *scene)
{
    char **properties = ft_split(line, ' ');

    if (!properties[1] || !properties[2] || !properties[3])
    {
        free(line);
        free(properties);
        free_gnl(scene->fd);
        exit_error(scene, "missing camera (C) settings", 1);
    }
    set_coordinates(properties[1], scene->camera.coordinates);
    set_normalization(properties[2], scene->camera.normalized);
    set_fov(properties[3], &scene->camera.fov);
    free_split(properties);
}

void    set_ambient(char *line, t_scene *scene)
{
    char **properties = ft_split(line, ' ');

    if (!properties[1] || !properties[2])
    {
        free(line);
        free(properties);
        free_gnl(scene->fd);
        exit_error(scene, "missing ambient light (A) settings", 1);
    }
    set_brightness(properties[1], &scene->ambient_light.brightness);
    set_rgb(properties[2], scene->ambient_light.rgb);
    free_split(properties);
}

void   set_light(char *line, t_scene *scene)
{
    char **properties = ft_split(line, ' ');

    if (!properties[1] || !properties[2] || !properties[3])
    {
        free(line);
        free(properties);
        free_gnl(scene->fd);
        exit_error(scene, "missing light (L) settings", 1);
    }
    set_coordinates(properties[1], scene->light.coordinates);
    set_brightness(properties[2], scene->light.brightness);
    set_rgb(properties[3], scene->light.rgb);
    free_split(properties);
}

void    set_plane(char *line, t_scene *scene, int i)
{
    char **properties = ft_split(line, ' ');

    if (!properties[1] || !properties[2] || !properties[3])
    {
        free(line);
        free(properties);
        free_gnl(scene->fd);
        exit_error(scene, "missing plane (pl) settings", 1);
    }
    set_coordinates(properties[1], scene->planes[i].coordinates);
    set_normalization(properties[2], scene->planes[i].normalized);
    set_rgb(properties[3], scene->planes[i].rgb);
    free_split(properties);
}

void    set_sphere(char *line, t_scene *scene, int i)
{
    char **properties = ft_split(line, ' ');

    if (!properties[1] || !properties[2] || !properties[3])
    {
        free(line);
        free(properties);
        free_gnl(scene->fd);
        exit_error(scene, "missing sphere (sp) settings", 1);
    }
    set_coordinates(properties[1], scene->spheres[i].coordinates);
    set_diameter(properties[2], &scene->spheres[i].diameter);
    set_rgb(properties[3], scene->spheres[i].rgb);
    free_split(properties);
}

void    set_cylinder(char *line, t_scene *scene, int i)
{
    char **properties = ft_split(line, ' ');

    if (!properties[1] || !properties[2] || !properties[3] || !properties[4] || !properties[5])
    {
        free(line);
        free(properties);
        free_gnl(scene->fd);
        exit_error(scene, "missing cylinder (cy) settings", 1);
    }
    set_coordinates(properties[1], scene->cylinders[i].coordinates);
    set_normalization(properties[2], scene->cylinders[i].normalized);
    set_diameter(properties[3], &scene->cylinders[i].diameter);
    set_height(properties[4], &scene->cylinders[i].height);
    set_rgb(properties[5], scene->cylinders[i].rgb);
    free_split(properties);
}
