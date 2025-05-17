#ifndef  MINIRT_H
# define MINIRT_H

#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <stdint.h> // check if allowed (uint32)
#include <stdbool.h>
#include <fcntl.h>
#include <math.h>

#define WIDTH 200
#define HEIGHT 200

enum e_id {
    A,
    C,
    L,
    PL,
    SP,
    CY
};

// typedef struct s_fixed {
//     unsigned int bits;
//     int fraction;
// } t_fixed;

typedef struct s_sphere {
    float coordinates[3]; // except A - because its ambient
    uint8_t rgb[3]; // except C - camera
    float diameter; // only sp and cy - because theyre circulars
} t_sphere;

typedef struct s_cylinder {
    float coordinates[3]; // except A - because its ambient
    float normalized[3]; // only pl, cy and C - because have planes
    uint8_t rgb[3]; // except C - camera
    float diameter; // only sp and cy - because theyre circulars
    float height; // only cy - because of volume
} t_cylinder;

typedef struct s_plane {
    float coordinates[3]; // except A - because its ambient
    float normalized[3]; // only pl, cy and C - because ?
    uint8_t rgb[3]; // except C - camera
} t_plane;

typedef struct s_camera {
    float coordinates[3]; // except A
    float normalized[3]; // only pl, cy and C
    float fov; // only C - camera
} t_camera;

typedef struct s_light {
    bool ambient; // flag to know light type
    float coordinates[3]; // except A - because its ambient
    float brightness[3]; // only A and L - because lights
    uint8_t rgb[3]; // except C
} t_light;

typedef struct s_scene {
    t_camera camera;
    t_light ambient_light;
    t_light *lights;

    t_sphere *spheres;
    t_plane *planes;
    t_cylinder *cylinders;
    uint32_t img[WIDTH * HEIGHT];
    int amount[6];
} t_scene;

// parse.c
t_scene    parse(char *file);
float   ft_atof(char *str);

// free.c
void free_scene(t_scene *scene);
void free_gnl(int fd);
void	free_split(char **array);

// error.c
void exit_error(t_scene* scene, char *msg, int ret);

// init.c
t_camera    init_camera();
t_light    init_ambient();
t_light    *init_lights(int amount);
t_plane    *init_planes(int amount);
t_sphere    *init_spheres(int amount);

// init2.c
t_cylinder    *init_cylinders(int amount);

// set_parser.c
float   *coordinates(char *str);
float   *normalization(char *str);
float   brightness(char *str);
float   diameter(char *str);
float   height(char *str);
uint8_t   *rgb(char *str);
uint8_t   fov(char *str);

#endif
