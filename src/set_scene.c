#include "../includes/minirt.h"
// tratar erros: passando t_scene para exit_error

void    set_camera(char *line, t_scene *scene)
{
    char **properties = ft_split(line, ' ');

    // if (!properties[1])
    //exit error
    set_coordinates(properties[1], scene->camera.coordinates);
    set_normalization(properties[2], scene->camera.normalized);
    set_fov(properties[3], &scene->camera.fov);
}

void    set_ambient(char *line, t_scene *scene)
{
    char **properties = ft_split(line, ' ');

    set_brightness(properties[1], scene->ambient_light.brightness);
    set_rgb(properties[2], scene->ambient_light.rgb);
    scene->ambient_light.ambient = 1;
}

void   set_light(char *line, t_scene *scene, int i)
{
    char **properties = ft_split(line, ' ');

    set_coordinates(properties[1], scene->lights[i].coordinates);
    set_brightness(properties[2], scene->lights[i].brightness);
    set_rgb(properties[3], scene->lights[i].rgb);
}

void    set_plane(char *line, t_scene *scene, int i)
{
    char **properties = ft_split(line, ' ');

    set_coordinates(properties[1], scene->planes[i].coordinates);
    set_normalization(properties[2], scene->planes[i].normalized);
    set_rgb(properties[3], scene->planes[i].rgb);
}

void    set_sphere(char *line, t_scene *scene, int i)
{
    char **properties = ft_split(line, ' ');

    set_coordinates(properties[1], scene->spheres[i].coordinates);
    set_normalization(properties[2], &scene->spheres[i].diameter);
    set_rgb(properties[3], scene->spheres[i].rgb);
}

void    set_cylinder(char *line, t_scene *scene, int i)
{
    char **properties = ft_split(line, ' ');

    set_coordinates(properties[1], scene->cylinders[i].coordinates);
    set_coordinates(properties[2], scene->cylinders[i].normalized);
    set_normalization(properties[3], &scene->cylinders[i].diameter);
    set_normalization(properties[4], &scene->cylinders[i].height);
    set_rgb(properties[5], scene->cylinders[i].rgb);
}
