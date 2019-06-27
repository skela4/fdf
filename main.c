/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 03:51:42 by lmarques          #+#    #+#             */
/*   Updated: 2019/06/27 05:21:03 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		abs(int a);

static	void	line(int x0, int y0, int x1, int y1, int z0, int z1, t_mlx *mlx, int color)
{ 

	x0 = (int)(0.71 * (x0 - y0)) + 400;
	y0 = (int)(-(-0.41 * (x0 + y0)) + 0.82 * -z0) + 400;
	x1 = (int)(0.71 * (x1 - y1)) + 400;
	y1 = (int)(-(-0.41 * (x1 + y1)) + 0.82 * -z1) + 400;

  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
	(*mlx).img.data[(y0 * 1200 + x0)] = color;
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

static	int		put_pixel(t_mlx *mlx, int x, int y, int color)
{
	(*mlx).img.data[(y * 1200 + x)] = color;
	return (0);
}

static	void	draw(t_mlx *mlx)
{
	int		y;
	int		x;

	y = 0;
	while (y < 11 - 1)
	{
		x = 0;
		while (x < 10 - 1)
		{

			printf("data[%d][%d] = %d\n", y, x, data[y][x]);
			line(x * 40, y * 40, (x + 1) * 40, y * 40, data[y][x], data[y][x + 1], &(*mlx), 0xFF0000);
			line((x + 1) * 40, y * 40, (x + 1) * 40, (y + 1) * 40, data[y][x + 1], data[y + 1][x + 1], &(*mlx), 0xFF0000);
			line(x * 40, y * 40, x * 40, (y + 1) * 40, data[y][x], data[y + 1][x], &(*mlx), 0xFF0000);
			line(x * 40, (y + 1) * 40, (x + 1) * 40, (y + 1) * 40, data[y + 1][x], data[y + 1][x + 1], &(*mlx), 0xFF0000);
			x++;
		}
		y++;
	}
}

int	main(void)
{
	t_mlx	mlx;
	
	if (!(mlx.ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(mlx.win = mlx_new_window(mlx.ptr, 1200, 1200, "Wire Frame")))
		return (EXIT_FAILURE);
	if (!(mlx.img.ptr = mlx_new_image(mlx.ptr, 1200, 1200)))
		return (EXIT_FAILURE);
	if (!(mlx.img.data = (int *)mlx_get_data_addr(mlx.img.ptr, &mlx.img.bpp,\
					&mlx.img.size, &mlx.img.endian)))
		return (EXIT_FAILURE);
	

	draw(&mlx);

	
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img.ptr, 0, 0);
	mlx_loop(mlx.ptr);
	return (0);
}
