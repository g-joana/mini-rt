#include "../../includes/minirt.h"

static int	set_diameter(char *str, float *diam)
{
    if (!valid_float(str))
        return 1;
	*diam = ft_atof(str);
    if (*diam < 0)
        return 1;
    return 0;
}

static int	set_height(char *str, float *height)
{
    if (!valid_float(str))
        return 1;
	*height = ft_atof(str);
    if (*height < 0)
        return 1;
    return 0;
}

void	set_cylinder(char **split, t_scene *scene, int i)
{
    int ret = 0;

	if (split_len(split) != 6)
        exit_set(split, scene, "invalid cylinder (cy) settings");
	ret += set_vec3d(split[1], &scene->cylinders[i].coord);
	ret += set_norm(split[2], &scene->cylinders[i].norm);
	ret += set_diameter(split[3], &scene->cylinders[i].diam);
	ret += set_height(split[4], &scene->cylinders[i].height);
	ret += set_rgb(split[5], &scene->cylinders[i].rgb);
	if (ret != 0)
        exit_set(split, scene, "invalid cylinder (cy) settings");
}

void	set_sphere(char **split, t_scene *scene, int i)
{
    int ret = 0;

	if (split_len(split) != 4)
        exit_set(split, scene, "invalid sphere (sp) settings");
	ret += set_vec3d(split[1], &scene->spheres[i].coord);
	ret += set_diameter(split[2], &scene->spheres[i].diam);
	ret += set_rgb(split[3], &scene->spheres[i].rgb);
	if (ret != 0)
        exit_set(split, scene, "invalid sphere (sp) settings");
}

void	set_plane(char **split, t_scene *scene, int i)
{
    int ret = 0;

	if (split_len(split) != 4)
        exit_set(split, scene, "invalid plane (pl) settings");
	ret += set_vec3d(split[1], &scene->planes[i].coord);
	ret += set_norm(split[2], &scene->planes[i].norm);
	ret += set_rgb(split[3], &scene->planes[i].rgb);
	if (ret != 0)
        exit_set(split, scene, "invalid plane (pl) settings");
}
