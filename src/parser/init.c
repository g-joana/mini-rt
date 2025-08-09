/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgils <jgils@student.42.rio>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:38:38 by jgils             #+#    #+#             */
/*   Updated: 2025/08/09 17:38:38 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	*count_elements(char *file);
static int	increment_elements_count(char *id, int *amount);

t_scene	*init_scene(char *file)
{
	t_scene	*scene;
	int		*amount;

	amount = count_elements(file);
	scene = (t_scene *)malloc(sizeof(t_scene));
	scene->amount = amount;
	if (scene->amount[A] != 1)
		exit_error(scene, "ERROR: scene needs 1 ambient light placed", 1);
	if (scene->amount[C] != 1)
		exit_error(scene, "ERROR: scene needs 1 camera placed", 1);
	if (scene->amount[L] != 1)
		exit_error(scene, "ERROR: scene needs 1 light placed", 1);
	scene->amb_light = init_ambient();
	scene->cam = init_camera();
	scene->light = init_light();
	if (scene->amount[PL])
		scene->planes = init_planes(scene->amount[PL]);
	if (scene->amount[SP])
		scene->spheres = init_spheres(scene->amount[SP]);
	if (scene->amount[CY])
		scene->cylinders = init_cylinders(scene->amount[CY]);
	return (scene);
}

static int	*count_elements(char *file)
{
	int		*amount;
	char	*id;
	char	*line;
	int		fd;

	amount = calloc(MAX_ELEMENTS, sizeof(int));
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		exit_count(amount, fd, line, "empty file");
	while (line)
	{
		id = get_first_word(line, 1);
		if (!increment_elements_count(id, amount))
		{
			free(id);
			exit_count(amount, fd, line, "invalid id");
		}
		if (id)
			free(id);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (amount);
}

char	*get_first_word(char *str, bool free_str)
{
	int		i;
	int		count;
	char	*word;

	i = 0;
	count = 0;
	if (str == NULL)
		return (NULL);
	while (str && str[i] == ' ')
		i++;
	while (str && str[i + count] != '\0' && str[i + count] != ' ')
		count++;
	word = malloc((count + 1) * sizeof(char));
	count = 0;
	while (str && str[i + count] != '\0' && str[i + count] != ' ')
	{
		word[count] = str[i + count];
		count++;
	}
	word[count] = '\0';
	return (word);
}

static int	increment_elements_count(char *id, int *amount)
{
	if (ft_strncmp("A", id, 2) == 0)
		amount[A]++;
	else if (ft_strncmp("C", id, 2) == 0)
		amount[C]++;
	else if (ft_strncmp("L", id, 2) == 0)
		amount[L]++;
	else if (ft_strncmp("pl", id, 3) == 0)
		amount[PL]++;
	else if (ft_strncmp("sp", id, 3) == 0)
		amount[SP]++;
	else if (ft_strncmp("cy", id, 3) == 0)
		amount[CY]++;
	else if (id[0] != '\n' && id[0] != '#')
		return (0);
	return (1);
}
