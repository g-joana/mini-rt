#include "../mlx/mlx.h"

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

typedef struct	s_data
{
	void	*mlx;
	void	*window;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_data;

typedef struct	s_circle
{
	int	xc;
	int	yc;
	int	r;
	int	color;
}		t_circle;

void	draw_circle(t_data img, t_circle circle);

int	main(void)
{
	t_data		img;
	t_circle 	circle;

	img.mlx = mlx_init();
	img.window = mlx_new_window(img.mlx, WIN_WIDTH, WIN_HEIGHT, "Rolling rolling rolling rolling...");
	draw_circle(img, circle);
	mlx_loop(img.mlx);
	return (0);
}

void	draw_circle(t_data img, t_circle circle)
{
	int	x_offset;
	int	y_offset;

	x_offset = 0;
	y_offset = circle.r;

	img.img = mlx_new_image(img.mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);

	return((void)0);
}
