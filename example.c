/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 03:51:42 by lmarques          #+#    #+#             */
/*   Updated: 2017/04/18 23:27:10 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "example.h"

int		abs(int a);


int	main(void)
{
	t_mlx	mlx;
	
	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "A simple example");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, 600, 600);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);
	

	mlx.img.data[(200 * 600 + 200) - 1] = 0xFF0000;
	mlx.img.data[(200 * 600 + 250) - 1] = 0x00FF00;
	mlx.img.data[(250 * 600 + 250) - 1] = 0x0000FF;
	mlx.img.data[(250 * 600 + 200) - 1] = 0xFFFFFF;
		

	// y = -0.41 * (x + y) + 0.82 * z      // x = 0.71 * (x - y)
	


	mlx.img.data[(int)(( -0.41 * (200 + 200) + 0.82  ) * 600 + (0.71 * (200 - 200))) - 1] = 0xFF0000;


	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
