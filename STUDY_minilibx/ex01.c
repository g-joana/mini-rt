#include "../mlx/mlx.h"

#define KEY_SPACE 49
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_pix;
	int		line_len;
	int		endian;
}			t_data;

void	shit_draw_screen(void *mlx, void *window);
void	put_pixel(t_data *img, int x, int y, int color);
void	draw_screen(void *mlx, void *window, t_data img);

int	main(void)
{
	t_data	img;
	void	*mlx;
	void	*window;

	(void)window;
	mlx = mlx_init();
	window = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Hi");
	shit_draw_screen(mlx, window);
	draw_screen(mlx, window, img);
	mlx_loop(mlx);
	return (0);
}

void	shit_draw_screen(void *mlx, void *window)
{
	int	x_len;
	int	y_len;
	
	x_len = WIN_WIDTH;
	y_len = WIN_HEIGHT;
	while (x_len > 0)
	{
	y_len = WIN_HEIGHT;
		while (y_len > 0)
		{
			mlx_pixel_put(mlx, window, x_len, y_len, 0xFF0000);
			y_len--;
		}
		x_len--;
	}
	return ((void)0);
}

void	draw_screen(void *mlx, void *window, t_data img)
{
	int	x_len;
	int	y_len;
	
	x_len = WIN_WIDTH;
	y_len = WIN_HEIGHT;
	img.img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_pix, &img.line_len, &img.endian);
	while (x_len > 0)
	{
		y_len = WIN_HEIGHT;
		while (y_len > 0)
		{
			put_pixel(&img, x_len, y_len, 0x00FF00);
			y_len--;
		}
		x_len--;
	}
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	return ((void)0);
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*pix;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		pix = data->addr + (y * data->line_len + x * (data->bits_pix / 8));
		*(unsigned int *)pix = color;
	}
	return ((void)0);
}
