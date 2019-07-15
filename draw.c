/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 02:18:12 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/13 07:57:58 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int			half_h;
	int			half_w;

	half_h = H / 2;
	half_w = W / 2;
	if (y + half_h >= 0 && y + half_h < H && x + half_w >= 0 && x + half_w < W)
		mlx->img.data[(y + half_h) * W + (x + half_w)] = color;
}

void			line(t_mlx *mlx, t_vec vec0, t_vec vec1)
{
	t_line		l;

	transform_fig(mlx, &vec0, &vec1);
	l.dx = abs(vec1.x - vec0.x);
	l.sx = vec0.x < vec1.x ? 1 : -1;
	l.dy = abs(vec1.y - vec0.y);
	l.sy = vec0.y < vec1.y ? 1 : -1;
	l.e1 = (l.dx > l.dy ? l.dx : -l.dy) / 2;
	while (1)
	{
		put_pixel(mlx, vec0.x, vec0.y, vec0.color);
		if (vec0.x == vec1.x && vec0.y == vec1.y)
			break ;
		l.e2 = l.e1;
		if (l.e2 > -l.dx)
		{
			l.e1 -= l.dy;
			vec0.x += l.sx;
		}
		if (l.e2 < l.dy)
		{
			l.e1 += l.dx;
			vec0.y += l.sy;
		}
	}
}

void			draw_line(t_mlx *mlx, t_map *m, t_vec *vec)
{
	int			y;
	int			x;
	int			yp;
	int			xp;

	y = 0;
	yp = 0;
	while (y < m->c)
	{
		x = 0;
		xp = 0;
		while (x < m->r)
		{
			line(mlx, vec[y * m->r + xp], vec[y * m->r + x]);
			line(mlx, vec[yp * m->r + x], vec[y * m->r + x]);
			x++;
			xp = x - 1;
		}
		y++;
		yp = y - 1;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}

void			draw_map(t_mlx *mlx, t_map *map, t_vec *vec)
{
	apply_axe(map, vec);
	apply_zoom(map, vec);
	apply_move(map, vec);
	draw_line(mlx, map, vec);
}

int				create_map(t_map *map)
{
	t_mlx		mlx;
	char		*tmp;
	t_vec		*vec_cpy;

	tmp = NULL;
	vec_cpy = NULL;
	if (!map)
		return (0);
	if (!(mlx_connect(&mlx)))
	{
		free_all(map, 1);
		return (0);
	}
	if (!(vec_cpy = copy_vec(map)))
		return (0);
	mlx.map = map;
	draw_map(&mlx, mlx.map, vec_cpy);
	tmp = (char *)vec_cpy;
	ft_strdel(&tmp);
	mlx_hook_function(&mlx);
	return (1);
}
