/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 09:53:21 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/03/27 12:12:31 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define ARROW_UP			126
#define ARROW_DOWN			125
#define ARROW_LEFT			123
#define ARROW_RIGHT			124

typedef struct	s_rect
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
}				t_rec;

typedef struct	s_img
{
	void		*ptr;
	int			*str;
	int			size;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
	t_img		img;
	int			posx;
	int			posy;
}				t_mlx;

static	void draw_line(t_rec rect, t_mlx **mlx, int err, int e2)
{
	int dx;
	int dy;
	int sx;
	int sy;

	if (rect.x0 == WIN_WIDTH)
		rect.x0 -= 1;
	if (rect.x1 == WIN_WIDTH)
		rect.x1 -= 1;
	if (rect.y0 == WIN_HEIGHT)
		rect.y0 -= 1;
	if (rect.y1 == WIN_HEIGHT)
		rect.y1 -= 1;

	dx = rect.x1 - rect.x0;
	sx = rect.x0 < rect.x1 ? 1 : -1;
	dy = rect.y1 - rect.y0;
	sy = rect.y0 < rect.y1 ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		(*mlx)->img.str[(rect.y0 * WIN_WIDTH) + (rect.x0)] = 0x0000FF;
		if (rect.x0 == rect.x1 && rect.y0 == rect.y1)
			return;
		e2 = err;
		if (e2 >-dx && (err -= dy))
			rect.x0 += sx;
		if (e2 < dy && (err += dx))
			rect.y0 += sy;
	}
}

static	void		draw_rec(t_mlx *mlx, int y0, int x0, int scale)
{
	t_rec	rect;
	
	rect.x0 = x0;
	rect.y0 = y0;
	rect.x1 = (WIN_WIDTH / scale) + rect.x0;
	rect.y1 = y0;

	// printf("x0 = %d y0 = %d x1 = %d y1 = %d\n", rect.x0, rect.y0, rect.x1, rect.y1);
	// printf("res = %d %d %d res = %d\n\n", rect.y0, WIN_HEIGHT, rect.x0, (rect.y0 * WIN_HEIGHT) + (rect.x0));
	
	draw_line(rect, &mlx, 0, 0);

	rect.x0 = rect.x1;
	rect.y1 = (WIN_HEIGHT / scale) + rect.y0;
	draw_line(rect, &mlx, 0, 0);

	rect.x0 = x0;
	rect.x1 = x0;
	draw_line(rect, &mlx, 0, 0);

	rect.y0 = rect.y1;
	rect.x1 = (WIN_WIDTH / scale) + rect.x0;
	draw_line(rect, &mlx, 0, 0);
}

static	int		key_hook(int key, void *param)
{
	t_mlx	*mlx;
	int		ret;

	mlx = (t_mlx *)param;

		printf("%d\n", key);


	if (key == ARROW_LEFT)
	{
		// ret = mlx_destroy_window(fdf->mlx, fdf->win);
		// printf("left");
		printf("%d\n", key);
		// mlx_destroy_image(mlx->ptr, mlx->img.ptr);
		mlx_clear_window (mlx->ptr, mlx->win);
		mlx->posx -= 1;
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, mlx->posx, mlx->posy);
	}
	if (key == ARROW_RIGHT)
	{
		// ret = mlx_destroy_window(fdf->mlx, fdf->win);
		// printf("left");
		printf("%d\n", key);
		// mlx_destroy_image(mlx->ptr, mlx->img.ptr);
		mlx_clear_window (mlx->ptr, mlx->win);
		mlx->posx += 1;
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, mlx->posx, mlx->posy);
	}
	if (key == ARROW_UP)
	{
		// ret = mlx_destroy_window(fdf->mlx, fdf->win);
		// printf("left");
		printf("%d\n", key);
		// mlx_destroy_image(mlx->ptr, mlx->img.ptr);
		mlx_clear_window (mlx->ptr, mlx->win);
		mlx->posy -= 1;
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, mlx->posx, mlx->posy);
	}
	if (key == ARROW_DOWN)
	{
		// ret = mlx_destroy_window(fdf->mlx, fdf->win);
		// printf("left");
		printf("%d\n", key);
		// mlx_destroy_image(mlx->ptr, mlx->img.ptr);
		mlx_clear_window (mlx->ptr, mlx->win);
		mlx->posy += 1;
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, mlx->posx, mlx->posy);
	}
	return (ret);
}

int					main(void)
{
	t_mlx			mlx;
	int			count_w;
	int			count_h;

	if (!(mlx.ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(mlx.win = mlx_new_window(mlx.ptr, WIN_WIDTH + 100, WIN_HEIGHT + 100, "Hello world")))
		return (EXIT_FAILURE);
	if (!(mlx.img.ptr = mlx_new_image(mlx.ptr, WIN_WIDTH, WIN_HEIGHT)))
		return (EXIT_FAILURE);
	mlx.img.str = (int *)mlx_get_data_addr(mlx.img.ptr, &mlx.img.bpp,\
	&mlx.img.size, &mlx.img.endian);

	int scale = 30;
	mlx.posx = 50;
	mlx.posy = 50;
	int col = WIN_HEIGHT / scale;
	int row = WIN_WIDTH / scale;

	count_h = 0;
	while (count_h < WIN_HEIGHT)
	{
		count_w = 0;
		while (count_w < WIN_WIDTH)
		{
			draw_rec(&mlx, count_h, count_w, scale);
			count_w += row;
		}
		count_h += col;
	}

	mlx_key_hook(mlx.win, &key_hook, &mlx);

	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img.ptr, mlx.posx, mlx.posy);
	mlx_loop(mlx.ptr);
	return (EXIT_SUCCESS);
}