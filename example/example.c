/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 03:51:42 by lmarques          #+#    #+#             */
/*   Updated: 2019/06/27 02:42:32 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "example.h"

static	void	draw(t_mlx *mlx_p)
{
	t_mlx	mlx;

	mlx = *mlx_p;

	mlx_clear_window(mlx.mlx_ptr, mlx.win);
	mlx.img.data[(mlx.pt.y * 600 + mlx.pt.x)] = 0x0000FF;
	printf("redraw\n");
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
}

static	int	left(int keycode, t_mlx *mlx_p)
{
	t_mlx	mlx;
	
	mlx = *mlx_p;
	if (keycode % 100 == 61)
	{
		mlx.pt.x -= 10;
	}
	printf("%d\n", mlx.pt.x);
	draw(&mlx);
}

int	main(void)
{
	t_mlx	mlx;
	
	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, 600, 600, "A simple example");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, 600, 600);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);

	mlx.pt.x = 300;
	mlx.pt.y = 300;
	mlx.pt.z = 10;

	printf("X1\n");
	draw(&mlx);
	printf("X2\n");

	mlx_key_hook(mlx.win, &left, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
