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

	x0 = (int)(0.71 * (x0 - y0)) + 250;
	y0 = (int)(-(-0.41 * (x0 + y0)) + 0.82 * -z0) + 250;
	x1 = (int)(0.71 * (x1 - y1)) + 250;
	y1 = (int)(-(-0.41 * (x1 + y1)) + 0.82 * -z1) + 250;

  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
	(*mlx).img.data[(y0 * 600 + x0)] = color;
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

static	int		put_pixel(t_mlx *mlx, int x, int y, int color)
{
	(*mlx).img.data[(y * 600 + x)] = color;
	return (0);
}

static	void	draw(t_mlx *mlx, t_point **pt)
{
	int		y;
	int		x;
	int		prey;
	int		prex;
	int		prez;

	y = 0;
	prey = 0;
	prez = (*pt)->z;
	while (y < 11)
	{
		x = 0;
		prex = 0;
		while (x < 19)
		{
			line(prex * 30, y * 30, x * 30, y * 30, pt[y * 19 + prex]->z, pt[y * 19 + x]->z, &(*mlx), 0xFF0000);	
			
			line(x * 30, prey * 30, x * 30, y * 30, pt[prey * 19 + x]->z, pt[y * 19 + x]->z, &(*mlx), 0xFF0000);
			
			x++;
			prex = x - 1;
		}
		y++;
		prey = y - 1;
	}
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_point	**pt;
	int		fd;
	
	if (!(mlx.ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(mlx.win = mlx_new_window(mlx.ptr, 600, 600, "Wire Frame")))
		return (EXIT_FAILURE);
	if (!(mlx.img.ptr = mlx_new_image(mlx.ptr, 600, 600)))
		return (EXIT_FAILURE);
	if (!(mlx.img.data = (int *)mlx_get_data_addr(mlx.img.ptr, &mlx.img.bpp,\
					&mlx.img.size, &mlx.img.endian)))
		return (EXIT_FAILURE);
	
	fd = open(argv[1], O_RDONLY);
	pt = ft_create_2d_tab(fd, NULL);

	draw(&mlx, pt);

	
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img.ptr, 0, 0);
	mlx_loop(mlx.ptr);
	return (0);
}
