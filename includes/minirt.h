#ifndef  MINIRT_H
# define MINIRT_H

#include "../libft/libft.h"
#include "../mlx/mlx.h"
// #include "../mlx/mlx_int.h"
#include <stdint.h> // check if allowed (uint32)
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include "../trivec/trivec.h"

#define WIDTH 400
#define HEIGHT 400

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
    t_vec3d *coord;
    uint8_t *rgb;
    float diam;
} t_sphere;

typedef struct s_cylinder {
    t_vec3d *coord;
    t_vec3d *norm;
    uint8_t *rgb;
    float diam;
    float height;
} t_cylinder;

typedef struct s_plane {
    t_vec3d *coord;
    t_vec3d *norm;
    uint8_t *rgb;
} t_plane;

typedef struct s_camera {
    t_vec3d *coord;
    t_vec3d *norm;
    uint8_t fov; // (horizontal) field of view
} t_camera;

typedef struct s_alight {
    float   bright;
    uint8_t *rgb;
} t_alight;

typedef struct s_light {
    t_vec3d *coord;
    float bright;
    uint8_t *rgb;
} t_light;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}			t_data;

typedef struct s_scene {
    int fd; // gambi de norma
    t_camera cam;
    t_alight amb_light;
    t_light light;

    t_sphere *spheres;
    t_plane *planes;
    t_cylinder *cylinders;
    // uint32_t img[WIDTH * HEIGHT];
    int *amount;

    void	*mlx;
    void	*mlx_win;
    t_data	img;
} t_scene;

// parse.c
t_scene    *parse(char *file);

// free.c
void free_scene(t_scene *scene);
void free_gnl(int fd);
void	free_split(char **array);
int	key_hook(int key, t_scene *scene);
int	mouse_hook(t_scene *scene);

// error.c
void exit_error(t_scene* scene, char *msg, int ret);

// init_setup.c
t_camera    init_camera();
t_alight    init_ambient();
t_light    init_light();

// init_shapes.c
t_cylinder    *init_cylinders(int amount);
t_plane    *init_planes(int amount);
t_sphere    *init_spheres(int amount);

// set_properties.c
void    set_coordinates(char *str, t_vec3d *coord);
void    set_normalization(char *str, t_vec3d *norm);
void    set_brightness(char *str, float *bright);
void    set_diameter(char *str, float *diam);
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
void   set_light(char *line, t_scene *scene);
void    set_plane(char *line, t_scene *scene, int i);
void    set_sphere(char *line, t_scene *scene, int i);
void    set_cylinder(char *line, t_scene *scene, int i);

// print.c
void print_scene(t_scene *scene);

// render.c
int    render(t_scene *scene);
void	start_mlx(t_scene *scene);

#endif
