#include "minilibx_macos/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define WIN_WIDTH 600
#define WIN_HEIGHT 300

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


static	void	iso(int x, int y, int z, t_mlx *mlx, int c)
{

	int previous_x;
	int previous_y;

	previous_x = x;
	previous_y = y;
	
	//(*mlx).img.str[(y * WIN_WIDTH) + x] = 0x00FF00;
	
	x = (previous_x - previous_y) * cos(0.523599);
	y = -z + (previous_x + previous_y) * sin(0.523599);

	//x = (x- z) / sqrt(2);
	//y = (x + 2 * y + z) / sqrt(6);

	(*mlx).img.str[(y * WIN_WIDTH) + x] = c;

}

int		main(void)
{
	int		map[2][2] = {  
		{0, 0},
		{0, 0}
	};
	int		map2[2][2] = {  
		{5, 5},
		{5, 5}
	};

	t_mlx			mlx;
	int			y;
	int			x;
	int			z;

	mlx.posx = 200;
	mlx.posy = 300;
	if (!(mlx.ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(mlx.win = mlx_new_window(mlx.ptr, WIN_WIDTH + 600, WIN_HEIGHT + 600, "Hello world")))
		return (EXIT_FAILURE);
	if (!(mlx.img.ptr = mlx_new_image(mlx.ptr, WIN_WIDTH, WIN_HEIGHT)))
		return (EXIT_FAILURE);
	mlx.img.str = (int *)mlx_get_data_addr(mlx.img.ptr, &mlx.img.bpp,\
			&mlx.img.size, &mlx.img.endian);

	y = 0;
	x = 0;
	while (y < 2)
	{
		x = 0;
		while (x < 2)
		{

			z = map[y][x];
			iso(x * WIN_WIDTH / 4, y * WIN_HEIGHT / 4, 0, &mlx, 0XFF0000);
			z = map2[y][x];
			iso(x * WIN_WIDTH / 4, y * WIN_HEIGHT / 4, 5, &mlx, 0X00FF00);
			x++;
		}
		y++;
	}


	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img.ptr, mlx.posx, mlx.posy);
	mlx_loop(mlx.ptr);
	return (EXIT_SUCCESS);

	return (0);
}
