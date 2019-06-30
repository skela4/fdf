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

/*void	mlx_create_point(t_mlx *mlx)
  {
  int		y;
  int		x;

  y = 0;
  x = 0;
  mlx->pt.scale = 150;
  mlx->pt.cols = (mlx->h / 2) / mlx->pt.scale;
  mlx->pt.rows = (mlx->w / 2) / mlx->pt.scale;
  mlx->pt.x = malloc(sizeof(x) * mlx->pt.rows * mlx->pt.cols);
  mlx->pt.y = malloc(sizeof(y) * mlx->pt.rows * mlx->pt.cols);
  mlx->pt.z = malloc(sizeof(x) * mlx->pt.rows * mlx->pt.cols);
  while (y <  mlx->pt.cols)
  {
  x = 0;
  while (x < mlx->pt.rows)
  {
  mlx->pt.y[y * mlx->pt.rows + x] = mlx->pt.scale * y;
  mlx->pt.x[y * mlx->pt.rows + x] = mlx->pt.scale * x;
  mlx->pt.z[y * mlx->pt.rows + x] = 0;
  x++;
  }
  y++;
  }
  }*/

/*static  void    line(t_mlx *mlx)
  { 
  int dx = abs(mlx->pt.l.x1 - mlx->pt.l.x0), sx = mlx->pt.l.x0 < mlx->pt.l.x1 ? 1 : -1;
  int dy = abs(mlx->pt.l.y1 - mlx->pt.l.y0), sy = mlx->pt.l.y0 < mlx->pt.l.y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;

  for(;;){
  mlx->img.data[(mlx->pt.l.y0 * 600 + mlx->pt.l.x0)] = mlx->pt.l.color;
  if (mlx->pt.l.x0 == mlx->pt.l.x1 && mlx->pt.l.y0 == mlx->pt.l.y1) break;
  e2 = err;
  if (e2 >-dx) { err -= dy; mlx->pt.l.x0 += sx; }
  if (e2 < dy) { err += dx; mlx->pt.l.y0 += sy; }
  }
  }
  */

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

static	void	put_pixel(t_mlx *mlx, int x, int y)
{
	mlx->img.data[(y + 200) * 600 + (x + 200)] = 0xFF0000;
}

void	mlx_draw_image(t_mlx *mlx, t_point **pt, int cols, int rows)
{
	int		y;
	int		x;
	
	y = 0;
	while (y < cols)
	{
		x = 0;
		while (x < rows)
		{
			put_pixel(&(*mlx), (*pt)[y * rows + x].x * 60 , (*pt)[y * rows + x].y * 60);
			x++;
		}

		y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
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

	pt = create_point(argc, argv, rows, cols);

	mlx_draw_image(&mlx, &pt, cols, rows);

	mlx_loop(mlx.mlx_ptr);

	mlx_disconnect(&mlx);

	free(mlx.mlx_ptr);
	mlx.mlx_ptr = NULL;
	return (0);
}
