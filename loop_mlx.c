/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 14:54:28 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/08 17:55:06 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			free_map(t_mlx *mlx)
{
	free(mlx->map->vec);
	mlx->map->vec = NULL;
	exit(EXIT_SUCCESS);
}

int				key_press(int keycode, void *param)
{
	t_mlx		*mlx;
	t_vec		*vec_cpy;
	char		*tmp;

	vec_cpy = NULL;
	tmp = NULL;
	mlx = (t_mlx *)param;
	vec_cpy = (t_vec *)ft_strnew(sizeof(*vec_cpy) * mlx->map->cr);
	ft_memcpy(vec_cpy, mlx->map->vec, sizeof(*vec_cpy) * mlx->map->cr);
	tmp = (char *)vec_cpy;
	ft_bzero(mlx->img.data, W * H * sizeof(int));
	
	if (keycode == 123)
		mlx->map->axe_y -=  M_PI / 90.0;
	else if (keycode == 124)
		mlx->map->axe_y +=  M_PI / 90.0;
	else if (keycode == 125)
		mlx->map->axe_x -=  M_PI / 90.0;
	else if (keycode == 126)
		mlx->map->axe_x +=  M_PI / 90.0;
	else if (keycode == 86)
		mlx->map->axe_z -=  M_PI / 90.0;
	else if (keycode == 88)
		mlx->map->axe_z +=  M_PI / 90.0;
	else if (keycode == 8)
	{
		//mlx->map->axe_x = 0.60;
		//mlx->map->axe_y = 0;
		//mlx->map->axe_z = 0.45;

		mlx->map->axe_x = 0.3526439;
		mlx->map->axe_y = 0.45;
		mlx->map->axe_z = 0.0;
	}

	printf("angle x == %f\n", 	mlx->map->axe_x);
	printf("angle y == %f\n", 	mlx->map->axe_y);
	printf("angle z == %f\n", 	mlx->map->axe_z);

	draw_map(mlx, mlx->map, vec_cpy);
	ft_strdel(&tmp);

	if (keycode == 53)
		free_map((t_mlx *)param);

	return (0);
}
