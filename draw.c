/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 06:42:55 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/04 12:52:48 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    put_pixel(t_mlx *mlx, int x, int y)
{
	mlx->img.data[(y + 500) * 1600 + (x + 500)] = 0xFF0000;
}

void    line(t_mlx *mlx, int x0, int y0, int x1, int y1, int z0, int z1)
{

	//x0 = (int)(0.71 * (x0 - y0)) + 210;
	//y0 = (int)(-(-0.41 * (x0 + y0)) + 0.82 * -z0) + 210;
	//x1 = (int)(0.71 * (x1 - y1)) + 210;
	//y1 = (int)(-(-0.41 * (x1 + y1)) + 0.82 * -z1) + 210;

	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;)
	{
		put_pixel(&(*mlx), x0 , y0);
		if (x0 == x1 && y0 == y1) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}

void    rotate_Z(t_point **pt, int cols, int rows, double angle)
{
	int     i;
	int     j;
	int		y;
	int		x;
	double  sin_theta;
	double  cos_theta;

	i = 0;
	j = 0;
	y = 0;
	x = 0;
	sin_theta = sin(angle);
	cos_theta = cos(angle);

	while (i < rows * cols)
	{
		printf("y = %d x = %d z = %d\n", (*pt)[i].y, (*pt)[i].x, (*pt)[i].z);
		i++;
	}

	i = 0;
	while (i < cols)
	{
		j = 0;
		while (j < rows)
		{
			x = (*pt)[i * rows + j].x;
			y = (*pt)[i * rows + j].y;
			(*pt)[i * rows + j].x = x * cos_theta - y * sin_theta;
			(*pt)[i * rows + j].y = x * sin_theta + y * cos_theta;
			j++;
		}
		i++;
	}
	//while (i < rows * cols)
	//{
//		x = (*pt)[i].x;
//		y = (*pt)[i].y;
//		(*pt)[i].x = x * cos_theta - y * sin_theta;
//		(*pt)[i].y = x * sin_theta + y * cos_theta;
//		i++;
//	}

	i = 0;
	while (i < rows * cols)
	{
		printf("y = %d x = %d z = %d\n", (*pt)[i].y, (*pt)[i].x, (*pt)[i].z);
		i++;
	}

}

int		key_hook(int keycode, void *param)
{
	t_mlx	mlx;

	mlx = *(t_mlx *)param;
	if (keycode == 123)
	{
		//gauche;
		mlx.angle = -90;
		bzero(mlx.img.data, mlx.w * mlx.h * sizeof(int));
		mlx_clear_window(mlx.mlx_ptr, mlx.win);
		rotate_Z(&(mlx.pt), mlx.pt->cols, mlx.pt->rows, mlx.angle);

		mlx_draw_image(&mlx, &(mlx.pt), mlx.pt->cols, mlx.pt->rows);
		//mlx_clear_image(&mlx);
		;
	}
	if (keycode == 126)
	{

		//mlx_clear_window(mlx.mlx_ptr, mlx.win);
		//haut;
		;
	}
	if (keycode == 124)
	{
		mlx.angle = 1;
		rotate_Z(&(mlx.pt), mlx.pt->cols, mlx.pt->rows, mlx.angle);
		mlx_draw_image(&mlx, &(mlx.pt), mlx.pt->cols, mlx.pt->rows);
		//droite;
		mlx.angle = 1;
		;
	}
	if (keycode == 125)
	{
		//bas;
		;
	}
	if (keycode == 53)
	{
		//exit;
		mlx_close_image(&mlx);
		mlx_disconnect(&mlx);
		exit(EXIT_SUCCESS);
	}
	printf("%d\n", keycode);
	return (0);
}

void    mlx_draw_image(t_mlx *mlx, t_point **pt, int cols, int rows)
{
	int             y;
	int             x;
	int             y_p;
	int             x_p;

	y = 0;
	y_p = 0;
	while (y < cols)
	{
		x = 0;
		x_p = 0;
		while (x < rows)
		{
			line(&*mlx, (*pt)[y * rows + x_p].x, (*pt)[y * rows + x_p].y, (*pt)[y * rows + x].x, (*pt)[y * rows + x].y, (*pt)[y * rows + x_p].z, (*pt)[y * rows + x].z);
			line(&*mlx, (*pt)[y_p * rows + x].x, (*pt)[y_p * rows + x].y, (*pt)[y * rows + x].x, (*pt)[y * rows + x].y, (*pt)[y_p * rows + x].z, (*pt)[y * rows + x].z);
			x++;
			x_p = x - 1;
		}
		y++;
		y_p = y - 1;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
}
