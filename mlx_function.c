/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 06:39:38 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/04 12:33:37 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    mlx_connect(t_mlx *mlx)
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

void    mlx_disconnect(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
}

void    mlx_create_image(t_mlx *mlx)
{
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->w, mlx->h);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);

}

void    mlx_clear_image(t_mlx *mlx)
{
	bzero(mlx->img.data, mlx->w * mlx->h * sizeof(int));
}

void    mlx_close_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
}
