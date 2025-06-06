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
        planes[i].coord = malloc(sizeof(t_vec3d) * 3);
        planes[i].coord->x = 0;
        planes[i].coord->y = 0;
        planes[i].coord->z = 0;
        planes[i].norm = malloc(sizeof(t_vec3d) * 3);
        planes[i].norm->x = 0;
        planes[i].norm->y = 0;
        planes[i].norm->z = 0;
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
        spheres[i].coord = malloc(sizeof(t_vec3d) * 3);
        spheres[i].coord->x = 0;
        spheres[i].coord->y = 0;
        spheres[i].coord->z = 0;
        spheres[i].rgb = malloc(sizeof(uint8_t) * 3);
        spheres[i].rgb[0] = 0;
        spheres[i].rgb[1] = 0;
        spheres[i].rgb[2] = 0;
        spheres[i].diam = 0;
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
        cylinders[i].coord = malloc(sizeof(t_vec3d) * 3);
        cylinders[i].coord->x = 0;
        cylinders[i].coord->y = 0;
        cylinders[i].coord->z = 0;
        cylinders[i].norm = malloc(sizeof(t_vec3d) * 3);
        cylinders[i].norm->x = 0;
        cylinders[i].norm->y = 0;
        cylinders[i].norm->z = 0;
        cylinders[i].rgb = malloc(sizeof(uint8_t) * 3);
        cylinders[i].rgb[0] = 0;
        cylinders[i].rgb[1] = 0;
        cylinders[i].rgb[2] = 0;
        cylinders[i].diam = 0;
        cylinders[i].height = 0;
        i++;
    }
    return (cylinders);
}
