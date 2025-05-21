#include "../includes/minirt.h"

void print_scene(t_scene *scene)
{
    // Print ambient light
    printf("Ambient Light:\n");
    printf("  Brightness: %f\n", scene->ambient_light.brightness);
    printf("  RGB: [%u, %u, %u]\n", 
        scene->ambient_light.rgb[0], 
        scene->ambient_light.rgb[1], 
        scene->ambient_light.rgb[2]);
    printf("\n");

    // Print camera
    printf("Camera:\n");
    printf("  Coordinates: [%f, %f, %f]\n", 
        scene->camera.coordinates[0], 
        scene->camera.coordinates[1], 
        scene->camera.coordinates[2]);
    printf("  Normalized: [%f, %f, %f]\n", 
        scene->camera.normalized[0], 
        scene->camera.normalized[1], 
        scene->camera.normalized[2]);
    printf("  FOV: %u\n", scene->camera.fov);
    printf("\n");

    // Print light
    printf("Light:\n");
    printf("  Coordinates: [%f, %f, %f]\n", 
        scene->light.coordinates[0], 
        scene->light.coordinates[1], 
        scene->light.coordinates[2]);
    printf("  Brightness: [%f, %f, %f]\n", 
        scene->light.brightness[0], 
        scene->light.brightness[1], 
        scene->light.brightness[2]);
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
            scene->spheres[i].coordinates[0], 
            scene->spheres[i].coordinates[1], 
            scene->spheres[i].coordinates[2]);
        printf("    RGB: [%u, %u, %u]\n", 
            scene->spheres[i].rgb[0], 
            scene->spheres[i].rgb[1], 
            scene->spheres[i].rgb[2]);
        printf("    Diameter: %f\n", scene->spheres[i].diameter);
    }
    printf("\n");

    // Print planes
    printf("Planes:\n");
    for (int i = 0; i < scene->amount[1]; i++) {
        printf("  Plane %d:\n", i + 1);
        printf("    Coordinates: [%f, %f, %f]\n", 
            scene->planes[i].coordinates[0], 
            scene->planes[i].coordinates[1], 
            scene->planes[i].coordinates[2]);
        printf("    Normalized: [%f, %f, %f]\n", 
            scene->planes[i].normalized[0], 
            scene->planes[i].normalized[1], 
            scene->planes[i].normalized[2]);
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
            scene->cylinders[i].coordinates[0], 
            scene->cylinders[i].coordinates[1], 
            scene->cylinders[i].coordinates[2]);
        printf("    Normalized: [%f, %f, %f]\n", 
            scene->cylinders[i].normalized[0], 
            scene->cylinders[i].normalized[1], 
            scene->cylinders[i].normalized[2]);
        printf("    RGB: [%u, %u, %u]\n", 
            scene->cylinders[i].rgb[0], 
            scene->cylinders[i].rgb[1], 
            scene->cylinders[i].rgb[2]);
        printf("    Diameter: %f\n", scene->cylinders[i].diameter);
        printf("    Height: %f\n", scene->cylinders[i].height);
    }
    printf("\n");
}