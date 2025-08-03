#include "../includes/minirt.h"

static void free_setup(t_scene *scene)
{
    free(scene->cam.coord);
    free(scene->cam.norm);
    free(scene->cam.foward);
    free(scene->cam.up);
    free(scene->cam.right);
    free(scene->amb_light.rgb);
    free(scene->light.coord);
    free(scene->light.rgb);
}

static void free_spheres(t_scene *scene)
{
    int count;

    if (scene->amount[SP])
    {
        count = 0;
        while (count < scene->amount[SP])
        {
            free(scene->spheres[count].coord);
            free(scene->spheres[count].rgb);
            count++;
        }
        free(scene->spheres);
    }
}

static void free_planes(t_scene *scene)
{
    int count;

    if (scene->amount[PL])
    {
        count = 0;
        while (count < scene->amount[PL])
        {
            free(scene->planes[count].coord);
            free(scene->planes[count].norm);
            free(scene->planes[count].rgb);
            count++;
        }
        free(scene->planes);
    }
}

static void free_cylinders(t_scene *scene)
{
    int count;

    if (scene->amount[CY])
    {
        count = 0;
        while (count < scene->amount[CY])
        {
            free(scene->cylinders[count].coord);
            free(scene->cylinders[count].norm);
            free(scene->cylinders[count].rgb);
            count++;
        }
        free(scene->cylinders);
    }
}

void free_scene(t_scene *scene)
{
    free_setup(scene);
    free_planes(scene);
    free_spheres(scene);
    free_cylinders(scene);
    free(scene->amount);
    free(scene);
}
