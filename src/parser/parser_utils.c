#include "../../includes/minirt.h"

float	round4(float value)
{
	return (((int)(value * 10000 + 0.5f)) / 10000.0f);
}

int	power(int base, int expoent)
{
	int	ret;

	ret = 1;
	while (expoent--)
		ret *= base;
	return (ret);
}

static float get_sign(char *str, int* i)
{
	float		sign;

    sign = 1.0f;
	while (str[*i] && str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (str[*i] && str[*i] == '-')
	{
		sign = -1.0f;
		(*i)++;
	}
	else if (str[*i] && str[*i] == '+' && str[*i + 1])
		(*i)++;
    return sign;
}

static float get_fract(char *str, int* i)
{
    float	fract;
	float		div;

    div = 10.0f;
    fract = 0.0f;
    (*i)++;
    while (str[*i] && ft_isdigit(str[*i]))
    {
        fract += (str[(*i)++] - '0') / div;
        div *= 10.0f;
    }
    return fract;
}

float	ft_atof(char *str)
{
	int		i;
	float		sign;
	float		div;
	float	ret;
	float	fract;

	i = 0;
    ret = 0.0f;
    div = 10.0f;
    fract = 0.0f;
    sign = get_sign(str, &i);
	while (str[i] && str[i] >= '0' && str[i] <= '9') 
		ret = ret * 10.0 + (str[i++] - '0');
	if (str[i] && str[i] == '.')
        fract = get_fract(str, &i);
	ret += fract;
	ret *= sign;
	return (ret);
}
