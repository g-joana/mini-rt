#include "../includes/minirt.h"
// init = malloca e seta os valores pra 0

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

t_alight    init_ambient()
{
    t_alight ambient;

    ambient.brightness = malloc(sizeof(float) * 3);
    ambient.brightness[0] = 0;
    ambient.brightness[1] = 0;
    ambient.brightness[2] = 0;
    ambient.rgb = malloc(sizeof(uint8_t) * 3);
    ambient.rgb[0] = 0;
    ambient.rgb[1] = 0;
    ambient.rgb[2] = 0;
    return (ambient);
}

t_light    init_light()
{
    t_light light ;

    light.coordinates = malloc(sizeof(float) * 3);
    light.coordinates[0] = 0;
    light.coordinates[1] = 0;
    light.coordinates[2] = 0;
    light.brightness = malloc(sizeof(float) * 3);
    light.brightness[0] = 0;
    light.brightness[1] = 0;
    light.brightness[2] = 0;
    light.rgb = malloc(sizeof(uint8_t) * 3);
    light.rgb[0] = 0;
    light.rgb[1] = 0;
    light.rgb[2] = 0;
    return (light);
}

t_plane    *init_planes(int amount)
{
    t_plane *planes ;

    planes = malloc(sizeof(t_plane) * amount);
    int i = 0;
    while (i < amount)
    {
        planes[i].coordinates = malloc(sizeof(float) * 3);
        planes[i].coordinates[0] = 0;
        planes[i].coordinates[1] = 0;
        planes[i].coordinates[2] = 0;
        planes[i].normalized = malloc(sizeof(float) * 3);
        planes[i].normalized[0] = 0;
        planes[i].normalized[1] = 0;
        planes[i].normalized[2] = 0;
        planes[i].rgb = malloc(sizeof(uint8_t) * 3);
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
        spheres[i].coordinates = malloc(sizeof(float) * 3);
        spheres[i].coordinates[0] = 0;
        spheres[i].coordinates[1] = 0;
        spheres[i].coordinates[2] = 0;
        spheres[i].rgb = malloc(sizeof(uint8_t) * 3);
        spheres[i].rgb[0] = 0;
        spheres[i].rgb[1] = 0;
        spheres[i].rgb[2] = 0;
        spheres[i].diameter = 0;
        i++;
    }
    return (spheres);
}
