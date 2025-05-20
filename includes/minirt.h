#ifndef  MINIRT_H
# define MINIRT_H

#include "../libft/libft.h"
#include "../mlx/mlx.h"
#include <stdint.h> // check if allowed (uint32)
#include <stdbool.h>
#include <stdio.h>
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
    float *coordinates;
    uint8_t *rgb;
    float diameter;
} t_sphere;

typedef struct s_cylinder {
    float *coordinates;
    float *normalized;
    uint8_t *rgb;
    float diameter;
    float height;
} t_cylinder;

typedef struct s_plane {
    float *coordinates;
    float *normalized;
    uint8_t *rgb;
} t_plane;

typedef struct s_camera {
    float *coordinates;
    float *normalized;
    uint8_t fov; // (horizontal) field of view
} t_camera;

typedef struct s_light {
    bool ambient; // flag to know light type
    float *coordinates; // except A - because its ambient
    float *brightness;
    uint8_t *rgb;
} t_light;

typedef struct s_scene {
    int fd; // gambi de norma
    t_camera camera;
    t_light ambient_light;
    t_light *lights;

    t_sphere *spheres;
    t_plane *planes;
    t_cylinder *cylinders;
    // uint32_t img[WIDTH * HEIGHT];
    int *amount;
} t_scene;

// parse.c
t_scene    *parse(char *file);
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

// set_properties.c
void    set_coordinates(char *str, float *coordinates);
void    set_normalization(char *str, float *normalization);
void    set_brightness(char *str, float *brightness);
void    set_diameter(char *str, float *diameter);
void    set_height(char *str, float *height);
void    set_rgb(char *str, uint8_t* rgb);
void    set_fov(char *str, uint8_t *fov);

// parser_utils.c
float round4(float value);
int	power(int base, int expoent);
float   ft_atof(char *str);

// set_scene.c
void    set_camera(char *line, t_scene *scene);
void    set_ambient(char *line, t_scene *scene);
void   set_light(char *line, t_scene *scene, int i);
void    set_plane(char *line, t_scene *scene, int i);
void    set_sphere(char *line, t_scene *scene, int i);
void    set_cylinder(char *line, t_scene *scene, int i);

#endif
