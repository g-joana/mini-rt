#include "../../includes/minirt.h"

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

