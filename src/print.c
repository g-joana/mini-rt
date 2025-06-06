#include "../includes/minirt.h"

void print_scene(t_scene *scene)
{
    // Print ambient light
    printf("Ambient Light:\n");
    printf("  Brightness: %f\n", scene->amb_light.bright);
    printf("  RGB: [%u, %u, %u]\n", 
        scene->amb_light.rgb[0], 
        scene->amb_light.rgb[1], 
        scene->amb_light.rgb[2]);
    printf("\n");

    // Print camera
    printf("Camera:\n");
    printf("  Coordinates: [%f, %f, %f]\n", 
        scene->cam.coord->x, 
        scene->cam.coord->y, 
        scene->cam.coord->z); 
    printf("  Normalized: [%f, %f, %f]\n", 
        scene->cam.norm->x, 
        scene->cam.norm->y, 
        scene->cam.norm->z);
    printf("  FOV: %f\n", scene->cam.fov);
    printf("\n");

    // Print light
    printf("Light:\n");
    printf("  Coordinates: [%f, %f, %f]\n", 
        scene->light.coord->x, 
        scene->light.coord->y, 
        scene->light.coord->z);
    printf("  Brightness: %f\n", 
        scene->light.bright); 
    printf("  RGB: [%u, %u, %u]\n", 
        scene->light.rgb[0], 
        scene->light.rgb[1], 
        scene->light.rgb[2]);
    printf("\n");

    // Print spheres
    printf("Spheres:\n");
    for (int i = 0; i < scene->amount[0]; i++) {
        printf("  Sphere %d:\n", i + 1);
        printf("    Coordinates: [%f, %f, %f]\n", 
            scene->spheres[i].coord->x, 
            scene->spheres[i].coord->y, 
            scene->spheres[i].coord->z);
        printf("    RGB: [%u, %u, %u]\n", 
            scene->spheres[i].rgb[0], 
            scene->spheres[i].rgb[1], 
            scene->spheres[i].rgb[2]);
        printf("    Diameter: %f\n", scene->spheres[i].diam);
    }
    printf("\n");

    // Print planes
    printf("Planes:\n");
    for (int i = 0; i < scene->amount[1]; i++) {
        printf("  Plane %d:\n", i + 1);
        printf("    Coordinates: [%f, %f, %f]\n", 
            scene->planes[i].coord->x, 
            scene->planes[i].coord->y, 
            scene->planes[i].coord->z);
        printf("    Normalized: [%f, %f, %f]\n", 
            scene->planes[i].norm->x, 
            scene->planes[i].norm->y, 
            scene->planes[i].norm->z);
        printf("    RGB: [%u, %u, %u]\n", 
            scene->planes[i].rgb[0], 
            scene->planes[i].rgb[1], 
            scene->planes[i].rgb[2]);
    }
    printf("\n");

    // Print cylinders
    printf("Cylinders:\n");
    for (int i = 0; i < scene->amount[2]; i++) {
        printf("  Cylinder %d:\n", i + 1);
        printf("    Coordinates: [%f, %f, %f]\n", 
            scene->cylinders[i].coord->x, 
            scene->cylinders[i].coord->y, 
            scene->cylinders[i].coord->z);
        printf("    Normalized: [%f, %f, %f]\n", 
            scene->cylinders[i].norm->x, 
            scene->cylinders[i].norm->y, 
            scene->cylinders[i].norm->z);
        printf("    RGB: [%u, %u, %u]\n", 
            scene->cylinders[i].rgb[0], 
            scene->cylinders[i].rgb[1], 
            scene->cylinders[i].rgb[2]);
        printf("    Diameter: %f\n", scene->cylinders[i].diam);
        printf("    Height: %f\n", scene->cylinders[i].height);
    }
    printf("\n");
}
