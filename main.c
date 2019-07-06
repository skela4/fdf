/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 06:38:33 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/06 07:16:05 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec 		        *init_vec(int cols, int rows)
{
	int             y;
	int             x;
	t_vec			*vec;

	y = 0;
	x = 0;
	vec = NULL;
	if (!(vec = (t_vec *)malloc(sizeof(*vec) * (rows * cols))))
		return (NULL);
	while (y < cols)
	{
		x = 0;
		while (x < rows)
		{
			vec[y * rows + x].x = x * 30;
			vec[y * rows + x].y = y * 30;
			vec[y * rows + x].z = 0;
			vec[y * rows + x].c = 0;
			x++;
		}
		y++;
	}
	return (vec);
}


t_vec					*create_vec(char *file, t_map *map)
{
	int					cols;
	int					rows;
	t_vec				*vec;

	vec = NULL;
	map->r = check_equal_line(file, 0);
	map->c = count_line(file);
	map->total = map->c * map->r;
	if (!(vec = init_vec(map->c, map->r)))
		return (NULL);
	if (!(get_info_map(&vec, map->r, file)))
	{
		free(vec);
		vec = NULL;
	}
	return (vec);
}

int                     main(int argc, char **argv)
{
	char				*file;
	t_mlx				mlx;
	t_vec				*vec;
	t_map				map;

	file = NULL;
	vec = NULL;
	if (argc != 2)
		return (0);
	file = argv[1];
	if (!(vec = create_vec(file, &map)))
		return (0);
	map.vec = vec;	
	mlx_connect(&mlx);
	mlx_create_image(&mlx);
	draw_map(&mlx, &map);
	mlx_loop(mlx.mlx_ptr);
	mlx_disconnect(&mlx);
	free(mlx.mlx_ptr);
	mlx.mlx_ptr = NULL;
	free(vec);
	vec = NULL;
	return (0);
}
