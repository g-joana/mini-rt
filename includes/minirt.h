#ifndef  MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
// #include "../mlx/mlx_int.h"
# include <stdint.h> // check if allowed (uint32)
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../trivec/trivec.h"
#include <float.h>

# define WIDTH 900
# define HEIGHT 600
# define MAX_ELEMENTS 6

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

    // camera orientation
    t_vec3d *foward;
    t_vec3d *right;
    t_vec3d *up;
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

    float aspect_ratio;
    float   scale;
} t_scene;

typedef struct s_hit {
    int id;
    float distance;
    t_vec3d position;
    t_vec3d direction;
    t_vec3d *shape_origin;
    uint8_t *rgb;
} t_hit;

/* -----[START OF PARSER RELATED FUNCTIONS]----- */

// parser.c
t_scene		*parser(char *file);

//init.c
t_scene		*init_scene(char *file);
char		*get_first_word(char *str, bool free_str);

// parser_utils.c
float	round4(float value);
int	power(int base, int expoent);
float	ft_atof(char *str);

// init_utils_scene.c
t_camera	init_camera();
t_alight	init_ambient();
t_light		init_light();

// init_utils_shapes.c
t_cylinder	*init_cylinders(int amount);
t_plane		*init_planes(int amount);
t_sphere	*init_spheres(int amount);

// set_properties.c
void    set_coordinates(char *str, t_vec3d *coord);
void    set_normalization(char *str, t_vec3d *norm);
void    set_brightness(char *str, float *bright);
void    set_rgb(char *str, uint8_t* rgb);
void    set_fov(char *str, uint8_t *fov);

// set_scene.c
void    set_camera(char *line, t_scene *scene);
void    set_ambient(char *line, t_scene *scene);
void	set_light(char *line, t_scene *scene);

// set_shapes.c
void    set_plane(char *line, t_scene *scene, int i);
void    set_sphere(char *line, t_scene *scene, int i);
void    set_cylinder(char *line, t_scene *scene, int i);
void    set_diameter(char *str, float *diam);
void    set_height(char *str, float *height);

/* ----------[END]---------- */

// free.c
void free_scene(t_scene *scene);
void free_gnl(int fd);
void	free_split(char **array);
int	key_hook(int key, t_scene *scene);
int	mouse_hook(t_scene *scene);

// error.c
void exit_error(t_scene* scene, char *msg, int ret);

// parser_utils.c
float round4(float value);
int	power(int base, int expoent);
float   ft_atof(char *str);

// print.c
void print_scene(t_scene *scene);

// render.c
int		render(t_scene *scene);
void	start_mlx(t_scene *scene);
t_vec3d cross_vecs(t_vec3d *a, t_vec3d *b);

// render_utils.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
float clamp(float n, float min, float max);
float clamp_color(float n);
uint32_t color_per_pixel(t_vec3d *vec, float alpha);

#endif
