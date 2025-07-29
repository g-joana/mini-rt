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

float	ft_atof(char *str)
{
	int		i;
	float		sign = 1.0f;
	float		div = 10.0f;
	float	ret = 0.0f;
	float	fract = 0.0f;

	i = 0;
	while (str[i] && str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] && str[i] == '-')
	{
		sign = -1.0f;
		i++;
	}
	else if (str[i] && str[i] == '+' && str[i + 1])
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9') 
	{
		ret = ret * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] && str[i] == '.')
	{
		i++;
		while (str[i] && ft_isdigit(str[i]))
		{
			fract += (str[i] - '0') / div;
			i++;
			div *= 10.0f;
		}
	}
	ret += fract;
	ret *= sign;
	return (ret);
}

float ref_atof(char *str)
{
	int		i;
	float		sign = 1.0f;
	float		div = 10.0f;
	float	ret = 0.0f;
	float	fract = 0.0f;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == ','))
		i++;
	if (str[i] && str[i] == '-')
	{
		sign = -1.0f;
		i++;
	}
	else if (str[i] && str[i] == '+' && str[i + 1])
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9') 
	{
		ret = ret * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] && str[i] == '.')
	{
		i++;
		while (str[i] && ft_isdigit(str[i]))
		{
			fract += (str[i] - '0') / div;
			i++;
			div *= 10.0f;
		}
	}
    str = str + i;
	ret += fract;
	ret *= sign;
	return (ret);
}
