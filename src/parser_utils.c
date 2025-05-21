#include "../includes/minirt.h"

// arredonda para 4 casas decimais
float round4(float value) {
    // val= 3.141592
    // * 10000 = 31415.92
    // + 0.5f (round & cast to int)
    // / 10000 = 3.1416
    return ((int)(value * 10000 + 0.5f)) / 10000.0f;
}

int	power(int base, int expoent)
{
	int	ret;

	ret = 1;
	while (expoent--)
		ret *= base;
	return (ret);
}

float   ft_atof(char *str)
{
    int i = 0;
    int count = 0;
    float ret = ft_atoi(str);
    while (str && str[i] && str[i] != '.')
        i++;
    if (str[i] && str[i] == '.')
    {
        i++;
        while (str[i+count] && ft_isdigit(str[i + count]))
            count++;
        if (count)
            ret += (float)ft_atoi(&str[i]) / power(10, count);
    }
    // ret = round4(ret);
    return(ret);
}
