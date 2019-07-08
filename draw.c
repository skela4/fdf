/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:14:28 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/08 17:43:14 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void			put_pixel(t_mlx *mlx, int x, int y, int color)
{
	if (y + H / 2 >= 0 && y + H / 2 < H && x + W / 2 >= 0 && x + W / 2 < W)
		mlx->img.data[(y + H / 2) * W + (x + W / 2)] = color;
}


void			line(t_mlx *mlx, t_vec vec0, t_vec vec1)
{
	t_line		l;

	l.dx = abs(vec1.x - vec0.x);
	l.sx = vec0.x < vec1.x ? 1 : -1;
	l.dy = abs(vec1.y - vec0.y);
	l.sy = vec0.y < vec1.y ? 1 : -1;
	l.e1 = (l.dx > l.dy ? l.dx : -l.dy) / 2;
	while (1)
	{
		put_pixel(mlx, vec0.x, vec0.y, vec0.color);
		if (vec0.x == vec1.x && vec0.y == vec1.y)
			break;
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

void			send_line(t_mlx *mlx, t_map *map, t_vec *vec)
{
	int			y;
	int			x;
	int			y_p;
	int			x_p;

	y = 0;
	y_p = 0;
	while (y < map->c)
	{
		x = 0;
		x_p = 0;
		while (x < map->r)
		{
			line(mlx, vec[y * map->r + x_p], vec[y * map->r + x]);
			line(mlx, vec[y_p * map->r + x], vec[y * map->r + x]);
			x++;
			x_p = x - 1;
		}
		y++;
		y_p = y - 1;
	}

	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}

void			apply_axe(t_map *map, t_vec *vec_cpy)
{
	int			i;

	i = 0;
	while (i < map->cr)
	{
		mat3_rot_x(map, map->axe_x, &(vec_cpy[i].x));
		mat3_rot_y(map, map->axe_y, &(vec_cpy[i].x));
		mat3_rot_z(map, map->axe_z, &(vec_cpy[i++].x));
	}
}

void			draw_map(t_mlx *mlx, t_map *map, t_vec *vec_cpy)
{
	apply_axe(map, vec_cpy);
	send_line(mlx, map, vec_cpy);
}

void			draw(t_map *map, t_vec *vec_cpy)
{
	t_mlx		mlx;
	char		*tmp;

	tmp = NULL;
	if (!map)
		exit(EXIT_FAILURE);
	mlx.mlx_ptr = mlx_init();
	if (!(mlx.mlx_ptr))
		return;
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, W, H, "FDF");
	if (!mlx.win_ptr)
		return;
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, W, H);
	if (!mlx.img.img_ptr)
		return;
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp,\
			&mlx.img.size_l, &mlx.img.endian);
	if (!mlx.img.data)
		return;
	vec_cpy = (t_vec *)ft_strnew(sizeof(*vec_cpy) * map->cr);
	ft_memcpy(vec_cpy, map->vec, sizeof(*vec_cpy) * map->cr);
	draw_map(&mlx, map, vec_cpy);
	tmp = (char *)vec_cpy;
	ft_strdel(&tmp);
	mlx.map = map;
	mlx_key_hook(mlx.win_ptr, &key_press, &mlx);
	mlx_hook(mlx.win_ptr, 2, 0, &key_press, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
