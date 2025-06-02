#include "../../includes/minirt.h"
// set = seta os valores no seu devido campo da struct
// cada elemento da cena tem sua propriedade, nesse arquivo setamos as propriedades

void set_coordinates(char *str, t_vec3d *coord)
{
    char **values = ft_split(str, ',');

    // range: fe
    coord->x = ft_atof(values[0]);
    coord->y = ft_atof(values[1]);
    coord->z = ft_atof(values[2]);
    free_split(values);
}

void set_normalization(char *str, t_vec3d *norm)
{
    char **values = ft_split(str, ',');

    // range: -1 ~ 1
    norm->x = ft_atof(values[0]);
    norm->y = ft_atof(values[1]);
    norm->z = ft_atof(values[2]);
    free_split(values);
}

void   set_brightness(char *str, float *bright)
{
    char **values = ft_split(str, ',');

    // range: 0.0 ~ 1.0
    *bright = ft_atof(values[0]);
    free_split(values);
}

void set_diameter(char *str, float *diam)
{
    char **values = ft_split(str, ',');

    // range: positivo (medida)
    *diam = ft_atof(values[0]);
    free_split(values);
}


void set_height(char *str, float *height)
{
    char **values = ft_split(str, ',');

    // range: positivo (medida)
    *height = ft_atof(values[0]);
    free_split(values);
}

void    set_rgb(char *str, uint8_t *rgb)
{
    char **values = ft_split(str, ',');

    // range: 0 ~ 255
    rgb[0] = ft_atoi(values[0]);
    rgb[1] = ft_atoi(values[1]);
    rgb[2] = ft_atoi(values[2]);
    free_split(values);
}

void   set_fov(char *str, uint8_t*fov)
{
    char **values = ft_split(str, ',');

    // range: 0 ~ 180
    *fov = ft_atoi(values[0]);
    free_split(values);
}
