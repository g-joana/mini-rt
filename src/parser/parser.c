/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:48:59 by nranna            #+#    #+#             */
/*   Updated: 2025/07/31 22:50:55 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_scene	*validade_init_scene(char *file);
static void		parse_line(char *line, t_scene *scene, int *count);

t_scene	*parser(char *file)
{
	t_scene	*scene;
	int		*count;
	char	*line;

	scene = validade_init_scene(file);
	count = (int *)calloc(MAX_ELEMENTS, sizeof(int));
	line = get_next_line(scene->fd);
	while (line)
	{
		parse_line(line, scene, count);
		free(line);
		line = get_next_line(scene->fd);
	}
	free(count);
	close(scene->fd);
	return (scene);
}

static t_scene	*validade_init_scene(char *file)
{
	t_scene	*scene;
	char	*dot;

	dot = ft_strrchr(file, '.');
	if (!dot || ft_strncmp(dot, ".rt", 4) != 0)
		exit_error(NULL, "invalid extension", 1);
	if (access(file, R_OK) != 0)
		exit_error(NULL, "invalid file or can't access", 1);
	scene = init_scene(file);
	scene->fd = open(file, O_RDONLY);
	if (scene->fd < 0)
	{
		free(scene);
		exit_error(NULL, "couldn't open file", 1);
	}
	return (scene);
}

static void	parse_line(char *str, t_scene *scene, int *count)
{
	char	*id;
	char	*line;

    line = str;
    line[ft_strlen(line) - 1] = ' ';
	id = get_first_word(line, 0); // leak -> change to get id
	if (!id || id[0] == '\n' || id[0] == '#')
	{
		free(id);
		return ;
	}
	if (ft_strncmp("A", id, 2) == 0)
		set_ambient(line, scene);
	else if (ft_strncmp("C", id, 2) == 0)
		set_camera(line, scene);
	else if (ft_strncmp("L", id, 2) == 0)
		set_light(line, scene);
	else if (ft_strncmp("pl", id, 3) == 0)
		set_plane(line, scene, count[PL]++);
	else if (ft_strncmp("sp", id, 3) == 0)
		set_sphere(line, scene, count[SP]++);
	else if (ft_strncmp("cy", id, 3) == 0)
		set_cylinder(line, scene, count[CY]++);
	free(id);
}
