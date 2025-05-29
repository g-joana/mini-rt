/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex00.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nranna <nranna@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:50:01 by nranna            #+#    #+#             */
/*   Updated: 2025/05/26 15:04:11 by nranna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"

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

void	put_pixel(t_data *data, int x, int y, int color);

int	main(void)
{
	void	*mlx;
	void	*window;
	t_data	img;

	//init part
	(void)window;
	mlx = mlx_init();
	window = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Hello World. :)");

	//render part
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_pix, &img.line_len, &img.endian);
	
	//draw
	put_pixel(&img, WIN_WIDTH / 2, WIN_HEIGHT / 2, 0xFF0000);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);

	//important to keep the program running until cntrl-c or sigint
	mlx_loop(mlx);
	return (0);
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
