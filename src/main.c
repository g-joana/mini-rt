#include "../includes/minirt.h"

int main(int argc, char **argv) {

    t_scene *scene;

    scene = malloc(sizeof(t_scene));
    scene = parse(argc, argv);
}
