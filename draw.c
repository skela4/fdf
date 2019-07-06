/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 06:38:08 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/06 07:18:25 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		put_pixel(t_mlx *mlx, int x, int y)
{
			mlx->img.data[(y + 550) * 1600 + (x + 550)] = 0xFF0000;
}

void				line(t_mlx *mlx, t_vec vec0, t_vec vec1)
{
	t_line			l;
	
	l.dx = abs(vec1.x - vec0.x);
	l.sx = vec0.x < vec1.x ? 1 : -1;	
	l.dy = abs(vec1.y - vec0.y);
	l.sy = vec0.y < vec1.y ? 1 : -1;
	l.err = (l.dx > l.dy ? l.dx : -l.dy) / 2;
	while (1)
	{
		put_pixel(mlx, vec0.x, vec0.y);
		if (vec0.x == vec1.x && vec0.y == vec1.y)
			break;
		l.e2 = l.err;
		if (l.e2 > -l.dx)
		{
			l.err -= l.dy;
			vec0.x += l.sx;
		}
		if (l.e2 < l.dy)
		{
			l.err += l.dx;
			vec0.y += l.sy;
		}
	}
}

void				draw_map(t_mlx *mlx, t_map *map)
{
	int             y;
	int             x;
	int             y_p;
	int             x_p;

	y = 0;
	y_p = 0;
	while (y < map->c)
	{
		x = 0;
		x_p = 0;
		while (x < map->r)
		{
			line(mlx, map->vec[y * map->r + x_p], map->vec[y * map->r + x]);
			line(mlx, map->vec[y_p * map->r + x], map->vec[y * map->r + x]);
			x++;
			x_p = x - 1;
		}
		y++;
		y_p = y - 1;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
}
