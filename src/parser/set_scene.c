#include "../../includes/minirt.h"

// set = seta os valores no seu devido campo da struct
// cada elemento da cena tem sua propriedade, nesse arquivo setamos os elementos
//
// tratar erros: se nao houver input (properties[index]) chamar exit_error
// problemas: free da gnl

int split_len(char **split)
{
    int i = 0;

    if (!split)
        return 0;
    while (split[i])
        i++;
    return i;
}

int valid_float(char *str)
{
    int i = 0;
    if (!str)
        return 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (ft_isdigit(str[i]))
        i++;
    if (str[i] == '.')
        i++;
    while (ft_isdigit(str[i]))
        i++;
    return (i == ft_strlen(str));
}

int valid_vec(char **split)
{
    int i = 0;
    int ret = 0;
    if (!split)
        return 0;
    if (split_len(split) != 3)
        return 0;
    while (i < 3)
    {
        ret = valid_float(split[i]);
        i++;
    }
    return ret;
}

void    set_vec3d(char *line, t_vec3d **vec)
{
    char **split;
    
    split = ft_split(line, ',');
    if (!valid_vec(split))
    {
        *vec = NULL;
        return;
    }
	(*vec)->x = ft_atof(split[0]);
	(*vec)->y = ft_atof(split[1]);
	(*vec)->z = ft_atof(split[2]);
}

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
    scene->cam.fov = ref_atof(split[3]);
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
	char	**properties;

	properties = ft_split(line, ' ');
	if (!properties[1] || !properties[2])
	{
		free(line);
		free(properties);
		free_gnl(scene->fd);
		exit_error(scene, "missing ambient light (A) settings", 1);
	}
	set_brightness(properties[1], &scene->amb_light.bright);
	set_rgb(properties[2], scene->amb_light.rgb);
	free_split(properties);
}

void	set_light(char *line, t_scene *scene)
{
	char	**properties;

	properties = ft_split(line, ' ');
	if (!properties[1] || !properties[2] || !properties[3])
	{
		free(line);
		free(properties);
		free_gnl(scene->fd);
		exit_error(scene, "missing light (L) settings", 1);
	}
	set_coordinates(properties[1], scene->light.coord);
	set_brightness(properties[2], &scene->light.bright);
	set_rgb(properties[3], scene->light.rgb);
	free_split(properties);
}
