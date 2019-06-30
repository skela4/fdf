/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 03:51:42 by lmarques          #+#    #+#             */
/*   Updated: 2019/06/30 06:44:06 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "example.h"

void	mlx_connect(t_mlx *mlx)
{
	mlx->w = W;
	mlx->h = H;
	if (!(mlx->mlx_ptr = mlx_init()))
		exit(EXIT_FAILURE);
	if (!(mlx->win = mlx_new_window(mlx->mlx_ptr, mlx->w, mlx->h, "FDF")))
	{
		free(mlx->mlx_ptr);
		mlx->mlx_ptr = NULL;
		exit(EXIT_FAILURE);
	}
}

void	mlx_disconnect(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
}

void	mlx_create_image(t_mlx *mlx)
{
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->w, mlx->h);

	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);

}

void	mlx_clear_image(t_mlx *mlx)
{
	bzero(mlx->img.data, mlx->w * mlx->h * 4);
}

void	mlx_close_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);	
}

static  void    line(t_mlx *mlx, int x0, int y0, int x1, int y1, int z0, int z1, int color)
{ 
	//int dx = abs(mlx->pt.l.x1 - mlx->pt.l.x0), sx = mlx->pt.l.x0 < mlx->pt.l.x1 ? 1 : -1;
	//int dy = abs(mlx->pt.l.y1 - mlx->pt.l.y0), sy = mlx->pt.l.y0 < mlx->pt.l.y1 ? 1 : -1; 
	//int err = (dx>dy ? dx : -dy)/2, e2;

	x0 = (int)(0.71 * (x0 - y0)) + 210;
	y0 = (int)(-(-0.41 * (x0 + y0)) + 0.82 * -z0) + 210;
	x1 = (int)(0.71 * (x1 - y1)) + 210;
	y1 = (int)(-(-0.41 * (x1 + y1)) + 0.82 * -z1) + 210;

	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;)
	{

		put_pixel(&(*mlx), x0 , y0);
		//mlx->img.data[(mlx->pt.l.y0 * 600 + mlx->pt.l.x0)] = mlx->pt.l.color;
		if (x0 == x1 && y0 == y1) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}


/*void	mlx_draw_image(t_mlx *mlx)
  {
  int		y;
  int		x;
  int		prev_y;
  int		prev_x;

  y = 0;
  prev_y = 0;
  while (y < mlx->pt.cols)
  {
  x = 0;
  prev_x = 0;
  while (x < mlx->pt.rows)
  {
  mlx->pt.l.x0 = mlx->pt.x[y * mlx->pt.rows + prev_x];
  mlx->pt.l.y0 = mlx->pt.y[y * mlx->pt.rows + x];
  mlx->pt.l.x1 = mlx->pt.x[y * mlx->pt.rows + x];
  mlx->pt.l.y1 = mlx->pt.y[y * mlx->pt.rows + x];
  mlx->pt.l.color = 0xFF0000;
  line(&(*mlx));
  mlx->pt.l.x0 = mlx->pt.x[y * mlx->pt.rows + x];
  mlx->pt.l.y0 = mlx->pt.y[prev_y * mlx->pt.rows + x];
  mlx->pt.l.x1 = mlx->pt.x[y * mlx->pt.rows + x];
  mlx->pt.l.y1 = mlx->pt.y[y * mlx->pt.rows + x];
  mlx->pt.l.color = 0xFF0000;
  line(&(*mlx));
  x++;
  prev_x = x - 1;
  }
  y++;
  prev_y = y - 1;
  }
  mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
  }*/



void	put_pixel(t_mlx *mlx, int x, int y)
{
	mlx->img.data[(y) * 600 + (x)] = 0xFF0000;
}

void	mlx_draw_image(t_mlx *mlx, t_point **pt, int cols, int rows)
{
	int		y;
	int		x;
	int		y_p;
	int		x_p;

	y = 0;
	y_p = 0;
	while (y < cols)
	{
		x = 0;
		x_p = 0;
		while (x < rows)
		{
			line(&*mlx, (*pt)[y * rows + x_p].x, (*pt)[y * rows + x].y, (*pt)[y * rows + x].x, (*pt)[y * rows + x_p].y, (*pt)[y * rows + x_p].z, (*pt)[y * rows + x].z , 0xFF0000);
			line(&*mlx, (*pt)[y * rows + x].x, (*pt)[y_p * rows + x].y, (*pt)[y * rows + x].x, (*pt)[y * rows + x_p].y, (*pt)[y_p * rows + x].z, (*pt)[y * rows + x].z , 0XFF0000);
			x++;
			x_p = x - 1;
		}
		y++;
		y_p = y - 1;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
}


static	int		key_hook(int keycode, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	if (keycode % 100 == 30)
	{
		mlx->angle = -1;
		rotate_Z(&*(mlx->pt), mlx->cols, mlx->rows, mlx->angle);
	}
	if (keycode % 100 == 32)
	{
		mlx->angle = 1;
		rotate_Z(&*(mlx->pt), mlx->cols, mlx->rows, mlx->angle);
	}
	mlx_clear_image(&*mlx);
	mlx_draw_image(&*mlx, &*(mlx->pt), mlx->cols, mlx->rows);
	return (0);
}

int	main(int argc, char **argv)
{
	int		cols;
	int		rows;
	t_mlx	mlx;
	t_point	*pt;

	cols = 0;
	rows = 0;
	pt = NULL;
	if (argc != 2)
		return (0);
	rows = count_line(argv[1]);
	cols = check_equal_line(argv[1]);

	mlx_connect(&mlx);

	mlx_create_image(&mlx);
	mlx.angle = 1;
	pt = create_point(argc, argv, rows, cols);

	int		i;
	while (i < cols * rows)
	{
		pt[i].y += 100;
		pt[i].x += 100;
		i++;
	}

	ft_putchar('X');

	mlx_draw_image(&mlx, &pt, cols, rows);

	mlx.pt = &pt;
	mlx.cols = cols;
	mlx.rows = rows;
	mlx_key_hook(mlx.win, (*key_hook), &mlx);

	ft_putchar('X');

	mlx_loop(mlx.mlx_ptr);

	mlx_disconnect(&mlx);

	free(mlx.mlx_ptr);
	mlx.mlx_ptr = NULL;
	return (0);
}
