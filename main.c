/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 03:51:42 by lmarques          #+#    #+#             */
/*   Updated: 2019/07/02 06:52:53 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		abs(int a);
static	void	draw(t_mlx *mlx, t_point **pt);

static	void	ft_exit(t_mlx **mlx_p)
{
	mlx_destroy_image((**mlx_p).ptr, (**mlx_p).img.ptr);
	mlx_destroy_window((**mlx_p).ptr, (**mlx_p).win);
	exit(0);
}

static	void	line(int x0, int y0, int x1, int y1, int z0, int z1, t_mlx *mlx, int color)
{ 

	x0 = (int)(0.71 * (x0 - y0)) + 210;
	y0 = (int)(-(-0.41 * (x0 + y0)) + 0.82 * -z0) + 210;
	x1 = (int)(0.71 * (x1 - y1)) + 210;
	y1 = (int)(-(-0.41 * (x1 + y1)) + 0.82 * -z1) + 210;

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

static	void	draw(t_mlx *mlx_p, t_point **pt)
{
	int		y;
	int		x;
	int		prey;
	int		prex;
	t_mlx	mlx;

	mlx = *mlx_p;
	y = 0;
	prey = 0;
	while (y < 11)
	{
		x = 0;
		prex = 0;
		while (x < 19)
		{
			line(pt[y * 19 + prex]->x, pt[y * 19 + x]->y, pt[y * 19 + x]->x, pt[y * 19 + x]->y, pt[y * 19 + prex]->z, pt[y * 19 + x]->z, &mlx, 0xFF0000);	
			
			line(pt[y * 19 + x]->x, pt[prey * 19 + x]->y, pt[y * 19 + x]->x, pt[y * 19 + x]->y, pt[prey * 19 + x]->z, pt[y * 19 + x]->z, &mlx, 0xFF0000);
			
			x++;
			prex = x - 1;
		}
		y++;
		prey = y - 1;
	}
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img.ptr, mlx.w, mlx.h);
}

static	int	key_hook(int keycode, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	if (keycode % 100 == 7)
		ft_exit(&mlx);
	if (keycode % 100 == 61)
		mlx->w -= 1;
	if (keycode % 100 == 62)
		mlx->h -= 1;
	if (keycode % 100 == 63)
		mlx->w += 1;
	if (keycode % 100 == 64)
		mlx->h += 1;

	draw(mlx, mlx->pt);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_point	**pt;
	int		fd;
	int		i;
	int		j;

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
	
	mlx.w = 0;
	mlx.h = 0;

	i = 0;
	while (i < 11)
	{
		j = 0;
		while (j < 19)
		{
			pt[i * 19 + j]->x = j * 30;
			pt[i * 19 + j]->y = i * 30;
			j++;
		}
		i++;
	}
	mlx.pt = pt;
	draw(&mlx, pt);
	mlx_key_hook(mlx.win, (*key_hook), &mlx);
	mlx_loop(mlx.ptr);
	return (0);
}
