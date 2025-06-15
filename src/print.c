#include "../includes/minirt.h"

#include "../includes/minirt.h"
#include <stdio.h> // Adicionado para printf

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
    printf("  FOV: %u\n", scene->cam.fov); // Usar %u para uint8_t
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
    if (scene->amount[SP] > 0) {
        printf("Spheres:\n");
        for (int i = 0; i < scene->amount[SP]; i++) { // Usar scene->amount[SP]
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
    } else {
        printf("Spheres:\n  No spheres found.\n");
    }
    printf("\n");

    // Print planes
    if (scene->amount[PL] > 0) {
        printf("Planes:\n"); // Removido \n inicial, pois já há um \n após as esferas
        for (int i = 0; i < scene->amount[PL]; i++) {
            printf("  Plane %d:\n", i + 1);
            printf("    Coordinates: [%f, %f, %f]\n",
                scene->planes[i].coord->x,
                scene->planes[i].coord->y,
                scene->planes[i].coord->z);
            printf("    Normalized: [%f, %f, %f]\n",
                scene->planes[i].norm->x,
                scene->planes[i].norm->y,
                scene->planes[i].norm->z);
            printf("    RGB: [%u, %u, %u]\n", // Usar %u para uint8_t
                scene->planes[i].rgb[0],
                scene->planes[i].rgb[1],
                scene->planes[i].rgb[2]);
        }
    } else {
        printf("Planes:\n  No planes found.\n"); // Removido \n inicial
    }
    printf("\n");

    // Print cylinders
    if (scene->amount[CY] > 0) {
        printf("Cylinders:\n"); // Usar scene->amount[CY]
        for (int i = 0; i < scene->amount[CY]; i++) {
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
    } else {
        printf("Cylinders:\n  No cylinders found.\n");
    }
    printf("\n");
}
