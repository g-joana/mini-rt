#include "../../includes/minirt.h"

/* set = set values on it's corresponding structs
 each element on scene has it's on properties and in this file we set them.
*/

void    set_vec3d(char *line, t_vec3d **vec)
{
    char **split;
    
    split = ft_split(line, ',');
    if (!valid_vec(split))
    {
        *vec = NULL;
        free(split);
        return;
    }
	(*vec)->x = ft_atof(split[0]);
	(*vec)->y = ft_atof(split[1]);
	(*vec)->z = ft_atof(split[2]);
    free(split);
}

// range: -1 ~ 1
void    set_norm(char *line, t_vec3d **vec)
{
	set_vec3d(line, vec);
    if ((*vec)->x < -1 || (*vec)->x > 1)
        *vec = NULL;
    else if ((*vec)->y < -1 || (*vec)->y > 1)
        *vec = NULL;
    else if ((*vec)->z < -1 || (*vec)->z > 1)
        *vec = NULL;
}

// range: 0 ~ 255
void    set_rgb(char *line, t_vec3d **vec)
{
	set_vec3d(line, vec);
    if ((*vec)->x < 0 || (*vec)->x > 255)
        *vec = NULL;
    else if ((*vec)->y < 0 || (*vec)->y > 255)
        *vec = NULL;
    else if ((*vec)->z < 0 || (*vec)->z > 255)
        *vec = NULL;
}

// range: 0.0 ~ 1.0
void	set_bright(char *str, float *bright)
{
	char	**values;

	values = ft_split(str, ',');
	*bright = ft_atof(values[0]);
	free_split(values);
}

// range: 0 ~ 180
void	set_fov(char *str, uint8_t *fov)
{
	char	**values;

	values = ft_split(str, ',');
	*fov = ft_atoi(values[0]);
	free_split(values);
}
