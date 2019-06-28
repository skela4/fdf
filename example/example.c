/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 03:51:42 by lmarques          #+#    #+#             */
/*   Updated: 2019/06/27 02:42:32 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "example.h"
#include <string.h>
#include <stdlib.h>

static	void	draw(t_mlx *mlx_p)
{
	t_mlx	mlx;

	mlx = *mlx_p;

	bzero((char *)mlx.img.data, 600 * 600 * 4);
	mlx.img.data[(*mlx.pt.y * 600 + *mlx.pt.x)] = 0xFF0000;
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
}


static	int	left(int keycode, t_mlx *mlx_p)
{
	t_mlx	mlx;
	
	mlx = *mlx_p;

	if (keycode % 100 == 61)
		*mlx.pt.x -= 1;
	if (keycode % 100 == 62)
		*mlx.pt.y -= 1;
	if (keycode % 100 == 63)
		*mlx.pt.x += 1;
	if (keycode % 100 == 64)
		*mlx.pt.y += 1;
	printf("redraw\n");
	draw(&mlx);
}

int	main(void)
{
	t_mlx	mlx;
	int	x;
	int	y;
	int	z;

	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, 600, 600, "A simple example");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, 600, 600);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);
	x = 300;
	y = 300;
	z = 10;
	mlx.pt.x = &x;
	mlx.pt.y = &y;
	mlx.pt.z = &z;

	draw(&mlx);
	mlx_key_hook(mlx.win, &left, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
