#include "minilibx_macos/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define WIN_WIDTH 600
#define WIN_HEIGHT 600

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

/*
   static  void draw_line(t_rec rect, t_mlx **mlx, int err, int e2)
   {
   int dx;
   int dy;
   int sx;
   int sy;

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
   */

static	void	line(int x0, int y0, int x1, int y1, t_mlx *mlx) {

	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs( y1 - y0), sy = y0 < y1 ? 1 : -1; 
	int err = (dx > dy ? dx : -dy) / 2, e2;

	if (x0 == WIN_WIDTH)
		x0 -= 1;
	if (x1 == WIN_WIDTH)
		x1 -= 1;
	if (y0 == WIN_HEIGHT)
		y0 -= 1;
	if (y1 == WIN_HEIGHT)
		y1 -= 1;
	while (1)
	{
		(*mlx).img.str[(y0 * WIN_WIDTH) + x0] = 0x0000FF;
		if (x0==x1 && y0==y1) break;
		e2 = err;
		if (e2 > -dx && (err += dy))
			x0 += sx;
		if (e2 < dy && (err += dx)) 
			y0 += sy;
	}
}


void	rect(int x, int y, t_mlx *mlx)
{
	line(x * WIN_WIDTH / 4, y * WIN_HEIGHT / 4, (x + 1) * WIN_WIDTH / 4, y * WIN_HEIGHT / 4, &*mlx);

	line(x * WIN_WIDTH / 4, y * WIN_HEIGHT / 4, x * WIN_WIDTH / 4, (y + 1) * WIN_HEIGHT / 4, &*mlx);

	//line(x * WIN_WIDTH / 4, y * WIN_HEIGHT / 4, (x + 1) * WIN_WIDTH / 4, y * WIN_HEIGHT / 4, &mlx);

	//line(x * WIN_WIDTH / 4, y * WIN_HEIGHT / 4, (x + 1) * WIN_WIDTH / 4, y * WIN_HEIGHT / 4, &mlx);
}


void	iso(int x, int y, int z, t_mlx *mlx)
{
	
	float mat[2][3] = 
	{
		{0.53f, 0.0f, -0.85f},
		{0.49f, 0.82f, 0.3f}
		//{0.69f, -0.58f, 0.43f}
	};

	x = mat[0][0] * x + mat[0][1] * y + mat[0][2] * z;
	y = mat[1][0] * x + mat[1][1] * y + mat[1][2] * z;

	

	line(x * WIN_WIDTH / 4, y * WIN_HEIGHT / 4, (x + 1) * WIN_WIDTH / 4, y * WIN_HEIGHT / 4, &*mlx);
	line((x + 1) * WIN_WIDTH / 4, y * WIN_HEIGHT / 4, (x + 1) * WIN_WIDTH / 4, (y + 1) * WIN_HEIGHT / 4, &*mlx);
	line(x * WIN_WIDTH / 4, y * WIN_HEIGHT / 4, x * WIN_WIDTH / 4, (y + 1) * WIN_HEIGHT / 4, &*mlx);
	line(x * WIN_WIDTH / 4, (y + 1) * WIN_HEIGHT / 4, (x + 1) * WIN_WIDTH / 4, (y + 1) * WIN_HEIGHT / 4, &*mlx);
}

int		main(void)
{
	int		map[4][4] = {  
		{0, 0, 0, 0},
		{0, 10, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

	t_mlx			mlx;
	int			y;
	int			x;
	int			z;

	mlx.posx = 50;
	mlx.posy = 50;
	if (!(mlx.ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(mlx.win = mlx_new_window(mlx.ptr, WIN_WIDTH + 100, WIN_HEIGHT + 100, "Hello world")))
		return (EXIT_FAILURE);
	if (!(mlx.img.ptr = mlx_new_image(mlx.ptr, WIN_WIDTH, WIN_HEIGHT)))
		return (EXIT_FAILURE);
	mlx.img.str = (int *)mlx_get_data_addr(mlx.img.ptr, &mlx.img.bpp,\
			&mlx.img.size, &mlx.img.endian);

	y = 0;
	x = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			// map[y / (WIN_HEIGHT / 4)][x (WIN_WIDTH / 4)];

			z = map[y][x];
			iso(x, y, z, &mlx);
			x++;
		}
		y++;
	}


	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img.ptr, mlx.posx, mlx.posy);
	mlx_loop(mlx.ptr);
	return (EXIT_SUCCESS);

	return (0);
}
