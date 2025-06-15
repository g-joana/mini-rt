/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:48:59 by nranna            #+#    #+#             */
/*   Updated: 2025/06/15 15:09:09 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <stdio.h>

static t_scene	*validade_init_scene(char *file);
static void		parse_line(char *line, t_scene *scene, int *count);
// put this last guy on libft
static int		ft_strcmp(const char *s1, const char *s2);

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
	if (!dot || ft_strcmp(dot, ".rt") != 0)
		exit_error(NULL, "ERROR: Invalid extension", 1);
	if (access(file, R_OK) != 0)
		exit_error(NULL, "ERROR: Can't access file", 1);
	scene = init_scene(file);
	scene->fd = open(file, O_RDONLY);
	if (scene->fd < 0)
	{
		free(scene);
		exit_error(NULL, "ERROR: Couldn't open file", 1);
	}
	return (scene);
}

static void	parse_line(char *line, t_scene *scene, int *count)
{
	char	*id;

	id = get_first_word(line, 0);
	if (!id || id[0] == '\n')
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



// TODO: coloque esse cara na libft (não esqueça de tirar o static)
static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
