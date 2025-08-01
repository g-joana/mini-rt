/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:52:34 by nranna            #+#    #+#             */
/*   Updated: 2025/07/31 22:49:23 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	*count_elements(char *file);
static int	increment_elements_count(char *id, int *amount);

t_scene	*init_scene(char *file)
{
	t_scene	*scene;
	int		*amount;

	scene = (t_scene *)malloc(sizeof(t_scene));
	amount = count_elements(file);
	scene->amount = amount;
	if (scene->amount[A] != 1)
		exit_error(NULL, "ERROR: scene needs 1 ambient light placed", 1);
	if (scene->amount[C] != 1)
		exit_error(NULL, "ERROR: scene needs 1 camera placed", 1);
	if (scene->amount[L] != 1)
		exit_error(NULL, "ERROR: scene needs 1 light placed", 1);
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
	int		fd;

	amount = calloc(MAX_ELEMENTS, sizeof(int));
	fd = open(file, O_RDONLY);
	id = get_first_word(get_next_line(fd), 1);
	if (!id)
		exit_error(NULL, "empty file", 1);
	while (id)
	{
		if (increment_elements_count(id, amount))
		{
			free(amount);
			free(id);
			free_gnl(fd);
			exit_error(NULL, "invalid id", 1);
		}
		free(id);
		id = get_first_word(get_next_line(fd), 1);
	}
	free(id);
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
	if (free_str)
		free(str);
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
	else if (id[0] != '\n')
		return (1);
	return (0);
}
