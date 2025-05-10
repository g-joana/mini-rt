#ifndef  MINIRT_H
# define MINIRT_H

#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <fcntl.h>

enum e_id {
    AMBIENT,
    CAM,
    LIGHT,
    PLANE,
    SPHERE,
    CYLINDER
};

typedef struct s_sphere {
    float coordinates[3]; // except A - because its ambient
    float diameter; // only sp and cy - because theyre circulars
    float rgb[3]; // except C - camera
} t_sphere;

typedef struct s_cylinder {
    float coordinates[3]; // except A - because its ambient
    float normalized[3]; // only pl, cy and C - because have planes
    float diameter; // only sp and cy - because theyre circulars
    float height; // only cy - because of volume
    float rgb[3]; // except C - camera
} t_cylinder;

typedef struct s_plane {
    float coordinates[3]; // except A - because its ambient
    float normalized[3]; // only pl, cy and C - because ?
    float rgb[3]; // except C - camera
} t_plane;

typedef struct s_camera {
    float coordinates[3]; // except A
    float normalized[3]; // only pl, cy and C
    float fov; // only C - camera
} t_camera;

typedef struct s_light {
    int ambient; // flag to know light type
    float coordinates[3]; // except A - because its ambient
    float brightness[3]; // only A and L - because lights
    float rgb[3]; // except C
} t_light;

typedef struct s_scene {
    t_camera *camera;
    t_light *ambient_light;
    t_light *light;

    t_sphere *spheres;
    t_plane *planes;
    t_cylinder *cylinders;
} t_scene;

// parse.c
void    parse(int argc, char **argv);

#endif
