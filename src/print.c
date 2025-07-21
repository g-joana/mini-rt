#include "../includes/minirt.h"

void print_scene(t_scene *scene)
{
    // Print ambient light
    printf("Ambient Light:\n");
    printf("  Brightness: %f\n", scene->amb_light.bright);
    printf("  RGB: [%f, %f, %f]\n",
        scene->amb_light.rgb->x,
        scene->amb_light.rgb->y,
        scene->amb_light.rgb->z);
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
    printf("  RGB: [%f, %f, %f]\n",
        scene->light.rgb->x,
        scene->light.rgb->y,
        scene->light.rgb->z);
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
            printf("    RGB: [%f, %f, %f]\n",
                scene->spheres[i].rgb->x,
                scene->spheres[i].rgb->y,
                scene->spheres[i].rgb->z);
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
            printf("    RGB: [%f, %f, %f]\n", // Usar %u para uint8_t
                scene->planes[i].rgb->x,
                scene->planes[i].rgb->y,
                scene->planes[i].rgb->z);
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
            printf("    RGB: [%f, %f, %f]\n",
                scene->cylinders[i].rgb->x,
                scene->cylinders[i].rgb->y,
                scene->cylinders[i].rgb->z);
            printf("    Diameter: %f\n", scene->cylinders[i].diam);
            printf("    Height: %f\n", scene->cylinders[i].height);
        }
    } else {
        printf("Cylinders:\n  No cylinders found.\n");
    }
    printf("\n");
}
