#include "../../includes/minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_len + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

/* if the number passes max/min, it returns max/min, else returns the number */
float clamp(float n, float min, float max){

	if (n < min)
		return min;
	if (n > max)
		return max;
	return n;
}

uint32_t color_per_pixel(t_vec3d *vec, float alpha)
{
	vec->x = clamp(vec->x, vec->x, 255.0f);
	vec->y = clamp(vec->y, vec->y, 255.0f);
	vec->z = clamp(vec->z, vec->z, 255.0f);
	uint8_t r = (uint8_t)(vec->x);
	uint8_t g = (uint8_t)(vec->y);
	uint8_t b = (uint8_t)(vec->z);
	uint8_t a = (uint8_t)(alpha);

	return (a << 24) | (r << 16) | (g << 8) | b;
}
//
// /* same as clamp, but fixed max(1) and fixed min(0) */
// float clamp_color(float n){
//
// 	if (n < 0)
// 		return 0;
// 	if (n > 1)
// 		return 1;
// 	return n;
// }
//
// uint32_t color_per_pixel(t_vec3d *vec, float alpha)
// {
// 	uint8_t r = (uint8_t)(clamp_color(vec->x) * 255.0f);
// 	uint8_t g = (uint8_t)(clamp_color(vec->y) * 255.0f);
// 	uint8_t b = (uint8_t)(clamp_color(vec->z) * 255.0f);
// 	uint8_t a = (uint8_t)(clamp_color(alpha) * 255.0f);
//
// 	return (a << 24) | (r << 16) | (g << 8) | b;
// }
