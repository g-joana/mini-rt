#include "../../includes/minirt.h"

// set = seta os valores no seu devido campo da struct
// cada elemento da cena tem sua propriedade, nesse arquivo setamos os elementos
//
// tratar erros: se nao houver input (properties[index]) chamar exit_error
// problemas: free da gnl

void	set_camera(char *line, t_scene *scene)
{
    char **split;

    split = ft_split(line, ' ');
	if (split_len(split) != 4)
	{
		free(line);
		free_gnl(scene->fd);
		exit_error(scene, "invalid camera (C) settings", 1);
	}
	set_vec3d(split[1], &scene->cam.coord);
    set_vec3d(split[2], &scene->cam.norm);
	if (scene->cam.coord == NULL || scene->cam.norm == NULL)
	{
		free(line);
		free_gnl(scene->fd);
		exit_error(scene, "invalid camera (C) settings", 1);
	}
    *scene->cam.norm = norm_vec(scene->cam.norm);
    scene->cam.fov = ft_atof(split[3]);
	t_vec3d up_direction = {0.0f, 1.0f, 0.0f};
	if (fabs(dot_vecs(scene->cam.norm, &up_direction)) > 0.99f) {
		up_direction = (t_vec3d){0.0f, 0.0f, 1.0f};
	}
	t_vec3d temp = cross_vecs(scene->cam.norm, &up_direction);
	*scene->cam.foward = norm_vec(scene->cam.norm);
	*scene->cam.right = norm_vec(&temp);
	*scene->cam.up = cross_vecs(scene->cam.foward, scene->cam.right);
}

void	set_ambient(char *line, t_scene *scene)
{
	char	**split;

	split = ft_split(line, ' ');
	if (split_len(split) != 3)
	{
		free(line);
		free(split);
		free_gnl(scene->fd);
		exit_error(scene, "missing ambient light (A) settings", 1);
	}
	set_bright(split[1], &scene->amb_light.bright);
    set_rgb(split[2], &scene->amb_light.rgb);
	free_split(split);
}

void	set_light(char *line, t_scene *scene)
{
	char	**split;

	split = ft_split(line, ' ');
	if (split_len(split) != 4)
	{
		free(line);
		free(split);
		free_gnl(scene->fd);
		exit_error(scene, "missing light (L) settings", 1);
	}
	set_vec3d(split[1], &scene->light.coord);
	set_bright(split[2], &scene->light.bright);
	set_rgb(split[3], &scene->light.rgb);
	free_split(split);
}
