#include "../includes/minirt.h"

int main(int argc, char **argv) {

    t_scene scene;

    if (argc != 2)
        exit_error(NULL, "no file", 1);
    scene = parse(argv[1]);
    if (scene.planes == NULL)
        ft_printf("NULL scene\n");
    printf("camera\n");
    printf("coords[0]: %f\n", scene.camera.coordinates[0]);
    printf("coords[1]: %f\n", scene.camera.coordinates[1]);
    printf("coords[2]: %f\n", scene.camera.coordinates[2]);
    printf("\n");
    printf("coords[0]: %f\n", scene.camera.normalized[0]);
    printf("coords[1]: %f\n", scene.camera.normalized[1]);
    printf("coords[2]: %f\n", scene.camera.normalized[2]);
    free_scene(&scene);
    return (0);
}
