#include "../../includes/minirt.h"
// init = malloca e seta os valores pra 0
// setup = camera, light, ambient light (elements that can only be declared once - capital letter)

t_camera    init_camera()
{
    t_camera cam;

    cam.coord = malloc(sizeof(t_vec3d) * 3);
    cam.coord->x = 0;
    cam.coord->y = 0;
    cam.coord->z = 0;
    cam.norm = malloc(sizeof(t_vec3d) * 3);
    cam.norm->x = 0;
    cam.norm->y = 0;
    cam.norm->z = 0;
    cam.fov = 0;
    return (cam);
}

t_alight    init_ambient()
{
    t_alight ambient;

    ambient.bright = 0;
    ambient.rgb = malloc(sizeof(uint8_t) * 3);
    ambient.rgb[0] = 0;
    ambient.rgb[1] = 0;
    ambient.rgb[2] = 0;
    return (ambient);
}

t_light    init_light()
{
    t_light light ;

    light.coord = malloc(sizeof(t_vec3d) * 3);
    light.coord->x = 0;
    light.coord->y = 0;
    light.coord->z = 0;
    light.rgb = malloc(sizeof(uint8_t) * 3);
    light.rgb[0] = 0;
    light.rgb[1] = 0;
    light.rgb[2] = 0;
    light.bright = 0;
    return (light);
}
