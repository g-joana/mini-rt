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

void	set_cylinder(char *line, t_scene *scene, int i)
{
	char	**split;
    int ret = 0;

	split = ft_split(line, ' ');
	if (split_len(split) != 6)
	{
		free(line);
		free_split(split);
		free_gnl(scene->fd);
		exit_error(scene, "invalid cylinder (cy) settings", 1);
	}
	ret += set_vec3d(split[1], &scene->cylinders[i].coord);
	ret += set_norm(split[2], &scene->cylinders[i].norm);
	ret += set_diameter(split[3], &scene->cylinders[i].diam);
	ret += set_height(split[4], &scene->cylinders[i].height);
	ret += set_rgb(split[5], &scene->cylinders[i].rgb);
	if (ret != 0)
	{
		free(line);
        free_split(split);
		free_gnl(scene->fd);
		exit_error(scene, "invalid cylinder (cy) settings", 1);
	}
	free_split(split);
}

void	set_sphere(char *line, t_scene *scene, int i)
{
	char	**split;
    int ret = 0;

	split = ft_split(line, ' ');
	if (split_len(split) != 4)
	{
		free(line);
		free(split);
		free_gnl(scene->fd);
		exit_error(scene, "invalid sphere (sp) settings", 1);
	}
	ret += set_vec3d(split[1], &scene->spheres[i].coord);
	ret += set_diameter(split[2], &scene->spheres[i].diam);
	ret += set_rgb(split[3], &scene->spheres[i].rgb);
	if (ret != 0)
	{
		free(line);
        free_split(split);
		free_gnl(scene->fd);
		exit_error(scene, "invalid sphere (sp) settings", 1);
	}
	free_split(split);
}

void	set_plane(char *line, t_scene *scene, int i)
{
	char	**split;
    int ret = 0;

	split = ft_split(line, ' ');
	if (split_len(split) != 4)
	{
		free(line);
		free(split);
		free_gnl(scene->fd);
		exit_error(scene, "invalid plane (pl) settings", 1);
	}
	ret += set_vec3d(split[1], &scene->planes[i].coord);
	ret += set_norm(split[2], &scene->planes[i].norm);
	ret += set_rgb(split[3], &scene->planes[i].rgb);
	if (ret != 0)
	{
		free(line);
        free_split(split);
		free_gnl(scene->fd);
		exit_error(scene, "invalid plane (pl) settings", 1);
	}
	free_split(split);
}
