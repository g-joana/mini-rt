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
	int		count;
	float	ret;

	i = 0;
	count = 0;
	ret = ft_atoi(str);
	while (str && str[i] && str[i] != '.')
		i++;
	if (str[i] && str[i] == '.')
	{
		i++;
		while (str[i + count] && ft_isdigit(str[i + count]))
			count++;
		if (count)
		{
		}
		ret += (float)ft_atoi(&str[i]) / power(10, count);
	}
	// ret = round4(ret);
	return (ret);
}
