/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 07:05:10 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/13 07:36:44 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				rotation_key(t_mlx *mlx, int key)
{
	if (key == 82)
	{
		mlx->map->iso = 0;
		mlx->map->para = 0;
		mlx->map->zoom = 1.0;
		mlx->map->move_x = 0.0;
		mlx->map->move_y = 0.0;
		mlx->map->axe_x = 0.0;
		mlx->map->axe_y = 0.0;
		mlx->map->axe_z = 0.0;
	}
	if (key == 83)
		mlx->map->axe_y -= M_PI / 180.0;
	if (key == 85)
		mlx->map->axe_y += M_PI / 180.0;
	if (key == 84)
		mlx->map->axe_x -= M_PI / 180.0;
	if (key == 87)
		mlx->map->axe_x += M_PI / 180.0;
	if (key == 86)
		mlx->map->axe_z -= M_PI / 180.0;
	if (key == 88)
		mlx->map->axe_z += M_PI / 180.0;
}

void				projection_key(t_mlx *mlx, int key)
{
	if (key == 34)
	{
		mlx->map->iso = 1;
		mlx->map->para = 0;
	}
	if (key == 35)
	{
		mlx->map->iso = 0;
		mlx->map->para = 1;
	}
}

void				zoom_key(t_mlx *mlx, int key)
{
	if (key == 78 && mlx->map->zoom > 0.01)
		mlx->map->zoom -= 0.01;
	if (key == 69)
		mlx->map->zoom += 0.01;
}

void				move_key(t_mlx *mlx, int key)
{
	if (key == 123)
		mlx->map->move_x -= 1.5;
	if (key == 124)
		mlx->map->move_x += 1.5;
	if (key == 126)
		mlx->map->move_y -= 1.5;
	if (key == 125)
		mlx->map->move_y += 1.5;
}

int					key_press(int keycode, void *param)
{
	t_mlx			*mlx;
	t_vec			*vec_cpy;

	mlx = (t_mlx *)param;
	if (!(vec_cpy = copy_vec(mlx->map)))
	{
		free_all(mlx->map, 1);
		exit(1);
	}
	ft_bzero(mlx->img.data, W * H * sizeof(int));
	if (keycode >= 34 && keycode <= 35)
		projection_key(mlx, keycode);
	if (keycode >= 82 && keycode <= 88)
		rotation_key(mlx, keycode);
	if (keycode == 78 || keycode == 69)
		zoom_key(mlx, keycode);
	if (keycode >= 123 && keycode <= 126)
		move_key(mlx, keycode);
	if (keycode == 53)
		close_window((void *)mlx);
	draw_map(mlx, mlx->map, vec_cpy);
	free(vec_cpy);
	vec_cpy = NULL;
	return (1);
}
