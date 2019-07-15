/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 02:24:18 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/13 07:58:09 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				close_window(void *param)
{
	t_mlx		*mlx;

	mlx = (t_mlx *)param;
	free_all(mlx->map, 1);
	exit(EXIT_SUCCESS);
}

int				mlx_connect(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, W, H, "fdf");
	if (!mlx->win_ptr)
		return (0);
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, W, H);
	if (!mlx->img.img_ptr)
		return (0);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp,\
			&mlx->img.size_l, &mlx->img.endian);
	if (!mlx->img.data)
		return (0);
	return (1);
}

void			mlx_hook_function(t_mlx *mlx)
{
	mlx_hook(mlx->win_ptr, 2, 0, &key_press, (void *)mlx);
	mlx_hook(mlx->win_ptr, 17, 0, &close_window, (void *)mlx);
	mlx_loop(mlx->mlx_ptr);
}
