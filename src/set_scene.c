#include "../includes/minirt.h"

float   *coordinates(char *str)
{
    float *coordinates = malloc(sizeof(float) * 3);
    char **values = ft_split(str, ',');

    // range: fe
    coordinates[0] = ft_atof(values[0]);
    coordinates[1] = ft_atof(values[1]);
    coordinates[2] = ft_atof(values[2]);
    free_split(values);
    return (coordinates);
}

float   *normalization(char *str)
{
    float *normalization = malloc(sizeof(float) * 3);
    char **values = ft_split(str, ',');

    // range: -1 ~ 1
    normalization[0] = ft_atof(values[0]);
    normalization[1] = ft_atof(values[1]);
    normalization[2] = ft_atof(values[2]);
    free_split(values);
    return (normalization);
}

float   brightness(char *str)
{
    float brightness;
    char **values = ft_split(str, ',');

    // range: 0.0 ~ 1.0
    brightness = ft_atof(values[0]);
    free_split(values);
    return (brightness);
}

float   diameter(char *str)
{
    float diameter;
    char **values = ft_split(str, ',');

    // range: positivo (medida)
    diameter = ft_atof(values[0]);
    free_split(values);
    return (diameter);
}


float   height(char *str)
{
    float height;
    char **values = ft_split(str, ',');

    // range: positivo (medida)
    height = ft_atof(values[0]);
    free_split(values);
    return (height);
}

uint8_t   *rgb(char *str)
{
    uint8_t *rgb = malloc(sizeof(uint8_t) * 3);
    char **values = ft_split(str, ',');

    // range: 0 ~ 255
    rgb[0] = ft_atoi(values[0]);
    rgb[1] = ft_atoi(values[1]);
    rgb[2] = ft_atoi(values[2]);
    free_split(values);
    return (rgb);
}

uint8_t   fov(char *str)
{
    float fov;
    char **values = ft_split(str, ',');

    // range: 0 ~ 180
    fov = ft_atoi(values[0]);
    free_split(values);
    return (fov);
}
