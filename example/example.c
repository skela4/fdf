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

int		abs(int a);



void line(int x0, int y0, int x1, int y1, t_mlx *mlx, int color)
{ 
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
	(*mlx).img.data[(y0 * 1200 + x0)] = color;
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

int		put_pixel(t_mlx *mlx, int x, int y, int color)
{
	if (x >= 1200 || y >= 1200)
		return (0);
	(*mlx).img.data[(y * 1200 + x)] = color;
	return (0);
}

int	main(void)
{
	t_mlx	mlx;
	
	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "A simple example");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, 1200, 1200);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);
		
	// y = -0.41 * (x + y) + 0.82 * z      // x = 0.71 * (x - y)
	
	put_pixel(&mlx, (int)(0.71f * (300.0f - 200.0f)), (int)(-(-0.41f * (300.0f + 200.0f)) + 0.82f * 0.0f), 0xFF0000);
	put_pixel(&mlx, (int)(0.71f * (350.0f - 200.0f)), (int)(-(-0.41f * (350.0f + 200.0f)) + 0.82f * 0.0f), 0xFF0000);
	put_pixel(&mlx, (int)(0.71f * (350.0f - 250.0f)), (int)(-(-0.41f * (350.0f + 250.0f)) + 0.82f * 0.0f), 0xFF0000);
	put_pixel(&mlx, (int)(0.71f * (300.0f - 250.0f)), (int)(-(-0.41f * (300.0f + 250.0f)) + 0.82f * 0.0f), 0xFF0000);

	put_pixel(&mlx, (int)(0.71f * (300.0f - 200.0f)), (int)(-(-0.41f * (300.0f + 200.0f)) + 0.82f * 50.0f), 0x00FF00);
	put_pixel(&mlx, (int)(0.71f * (350.0f - 200.0f)), (int)(-(-0.41f * (350.0f + 200.0f)) + 0.82f * 50.0f), 0x00FF00);
	put_pixel(&mlx, (int)(0.71f * (350.0f - 250.0f)), (int)(-(-0.41f * (350.0f + 250.0f)) + 0.82f * 50.0f), 0x00FF00);
	put_pixel(&mlx, (int)(0.71f * (300.0f - 250.0f)), (int)(-(-0.41f * (300.0f + 250.0f)) + 0.82f * 50.0f), 0x00FF00);
	
	// line(x0 y0 x1 y1);
	line((int)(0.71f * (300.0f - 200.0f)), (int)(-(-0.41f * (300.0f + 200.0f)) + 0.82f * 0.0f),\
	(int)(0.71f * (350.0f - 200.0f)), (int)(-(-0.41f * (350.0f + 200.0f)) + 0.82f * 0.0f), &mlx, 0x00FFFF);

	line((int)(0.71f * (350.0f - 200.0f)), (int)(-(-0.41f * (350.0f + 200.0f)) + 0.82f * 0.0f),\
	(int)(0.71f * (350.0f - 250.0f)), (int)(-(-0.41f * (350.0f + 250.0f)) + 0.82f * 0.0f), &mlx, 0x00FFFF);
	
	line((int)(0.71f * (350.0f - 250.0f)), (int)(-(-0.41f * (350.0f + 250.0f)) + 0.82f * 0.0f),\
	(int)(0.71f * (300.0f - 250.0f)), (int)(-(-0.41f * (300.0f + 250.0f)) + 0.82f * 0.0f), &mlx, 0x00FFFF);

	line((int)(0.71f * (300.0f - 250.0f)), (int)(-(-0.41f * (300.0f + 250.0f)) + 0.82f * 0.0f),\
	(int)(0.71f * (300.0f - 200.0f)), (int)(-(-0.41f * (300.0f + 200.0f)) + 0.82f * 0.0f), &mlx, 0x00FFFF);


	line((int)(0.71f * (300.0f - 200.0f)), (int)(-(-0.41f * (300.0f + 200.0f)) + 0.82f * 50.0f),\
	(int)(0.71f * (350.0f - 200.0f)), (int)(-(-0.41f * (350.0f + 200.0f)) + 0.82f * 50.0f), &mlx, 0x00FFFF);

	line((int)(0.71f * (350.0f - 200.0f)), (int)(-(-0.41f * (350.0f + 200.0f)) + 0.82f * 50.0f),\
	(int)(0.71f * (350.0f - 250.0f)), (int)(-(-0.41f * (350.0f + 250.0f)) + 0.82f * 50.0f), &mlx, 0x00FFFF);
	
	line((int)(0.71f * (350.0f - 250.0f)), (int)(-(-0.41f * (350.0f + 250.0f)) + 0.82f * 50.0f),\
	(int)(0.71f * (300.0f - 250.0f)), (int)(-(-0.41f * (300.0f + 250.0f)) + 0.82f * 50.0f), &mlx, 0x00FFFF);

	line((int)(0.71f * (300.0f - 250.0f)), (int)(-(-0.41f * (300.0f + 250.0f)) + 0.82f * 50.0f),\
	(int)(0.71f * (300.0f - 200.0f)), (int)(-(-0.41f * (300.0f + 200.0f)) + 0.82f * 50.0f), &mlx, 0x00FFFF);
	

	line((int)(0.71f * (300.0f - 200.0f)), (int)(-(-0.41f * (300.0f + 200.0f)) + 0.82f * 0.0f),\
	(int)(0.71f * (300.0f - 200.0f)), (int)(-(-0.41f * (300.0f + 200.0f)) + 0.82f * 50.0f), &mlx, 0x00FFFF);

	line((int)(0.71f * (350.0f - 200.0f)), (int)(-(-0.41f * (350.0f + 200.0f)) + 0.82f * 0.0f),\
	(int)(0.71f * (350.0f - 200.0f)), (int)(-(-0.41f * (350.0f + 200.0f)) + 0.82f * 50.0f), &mlx, 0x00FFFF);

	line((int)(0.71f * (350.0f - 250.0f)), (int)(-(-0.41f * (350.0f + 250.0f)) + 0.82f * 0.0f),\
	(int)(0.71f * (350.0f - 250.0f)), (int)(-(-0.41f * (350.0f + 250.0f)) + 0.82f * 50.0f), &mlx, 0x00FFFF);

	line((int)(0.71f * (300.0f - 250.0f)), (int)(-(-0.41f * (300.0f + 250.0f)) + 0.82f * 0.0f),\
	(int)(0.71f * (300.0f - 250.0f)), (int)(-(-0.41f * (300.0f + 250.0f)) + 0.82f * 50.0f), &mlx, 0x00FFFF);



	//line(, &mlx, 0x00FFFF);

	//line(, &mlx, 0x00FFFF);
	
	//line(, &mlx, 0x00FFFF);
	
	//line(, &mlx, 0x00FFFF);
	
	//line(, &mlx, 0x00FFFF);
	
	//line(, &mlx, 0x00FFFF);
	
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
