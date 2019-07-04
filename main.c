/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 06:38:33 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/04 12:34:26 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point         *init_point(int cols, int rows)
{
	int             y;
	int             x;
	t_point *pt;

	y = 0;
	x = 0;
	pt = NULL;
	if (!(pt = (t_point *)malloc(sizeof(*pt) * (rows * cols))))
		return (NULL);
	while (y < cols)
	{
		x = 0;
		while (x < rows)
		{
			pt[y * rows + x].x = x;
			pt[y * rows + x].y = y;
			pt[y * rows + x].z = 0;
			pt[y * rows + x].color = 0;
			pt[y * rows + x].rows = rows;
			pt[y * rows + x].cols = cols;
			x++;
		}
		y++;
	}
	return (pt);
}


t_point         *create_point(char *file)
{
	int             cols;
	int             rows;
	t_point *pt;

	rows = check_equal_line(file, 0);
	cols = count_line(file);
	if (!(pt = init_point(cols, rows)))
		return (NULL);
	if (!(get_info_map(&pt, rows, file)))
	{
		free(pt);
		pt = NULL;
	}
	return (pt);
}

int                     main(int argc, char **argv)
{
	t_mlx   mlx;
	char    *file;
	t_point *pt;
	int             i;
	int             j;

	file = NULL;
	pt = NULL;
	if (argc != 2)
		return (0);
	file = argv[1];
	if (!(pt = create_point(file)))
		return (0);

	i = 0;
	while (i < pt->cols)
	{
		j = 0;
		while (j < pt->rows)
		{
			pt[i * pt->rows + j].x = j * 30.0;
			pt[i * pt->rows + j].y = i * 30.0;
			j++;
		}
		i++;
	}

	mlx_connect(&mlx);
	mlx_create_image(&mlx);

	mlx.pt = pt;

	mlx_draw_image(&mlx, &pt, pt->cols, pt->rows);
	ft_putnbr(mlx.w);
	
	
	
	mlx_key_hook(mlx.win, &key_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);
	mlx_disconnect(&mlx);
	free(mlx.mlx_ptr);
	mlx.mlx_ptr = NULL;
	free(pt);
	pt = NULL;
	return (0);
}
