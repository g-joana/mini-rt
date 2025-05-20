#include "../includes/minirt.h"

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
