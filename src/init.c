#include "../includes/minirt.h"

t_camera    init_camera()
{
    t_camera camera ;

    camera.coordinates = malloc(sizeof(float) * 3);
    camera.coordinates[0] = 0;
    camera.coordinates[1] = 0;
    camera.coordinates[2] = 0;
    camera.normalized = malloc(sizeof(float) * 3);
    camera.normalized[0] = 0;
    camera.normalized[1] = 0;
    camera.normalized[2] = 0;
    camera.fov = 0;
    return (camera);
}

t_light    init_ambient()
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
        i++;
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
        i++;
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
        i++;
    }
    return (spheres);
}
