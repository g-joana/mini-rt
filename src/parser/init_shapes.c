#include "../../includes/minirt.h"
// init = malloca e seta os valores pra 0
// shapes = sphere, plane, cylinder

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

t_cylinder    *init_cylinders(int amount)
{
    t_cylinder *cylinders ;

    cylinders = malloc(sizeof(t_cylinder) * amount);
    int i = 0;
    while (i < amount)
    {
        cylinders[i].coordinates = malloc(sizeof(float) * 3);
        cylinders[i].coordinates[0] = 0;
        cylinders[i].coordinates[1] = 0;
        cylinders[i].coordinates[2] = 0;
        cylinders[i].normalized = malloc(sizeof(float) * 3);
        cylinders[i].normalized[0] = 0;
        cylinders[i].normalized[1] = 0;
        cylinders[i].normalized[2] = 0;
        cylinders[i].rgb = malloc(sizeof(uint8_t) * 3);
        cylinders[i].rgb[0] = 0;
        cylinders[i].rgb[1] = 0;
        cylinders[i].rgb[2] = 0;
        cylinders[i].diameter = 0;
        cylinders[i].height = 0;
        i++;
    }
    return (cylinders);
}
