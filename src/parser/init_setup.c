#include "../../includes/minirt.h"
// init = malloca e seta os valores pra 0
// setup = camera, light, ambient light (elements that can only be declared once - capital letter)

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

    ambient.brightness = 0;
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
