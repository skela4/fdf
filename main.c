/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 02:47:30 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/08 16:54:14 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	t_file			file_info(char *file)
{
	t_file				info;

	info.nb_line = count_line(file);
	info.len_line = length_line(file);
	info.st_line = first_line(file);
	if (!info.nb_line)
	{
		ft_putendl_fd("No data found", 2);
		exit(EXIT_FAILURE);
	}
	else if (info.nb_line && !info.st_line)
	{
		ft_putendl_fd("No data found", 2);
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_putstr("number of line == ");
		ft_putnbr(info.nb_line);
		ft_putchar('\n');
		ft_putstr("length of line == ");
		ft_putnbr(info.len_line);
		ft_putchar('\n');
	}
	return (info);
}

int						calc_dist(int cols, int rows, int small_size)
{
	int					dist;
	int					hyp;

	dist = 1;
	hyp = pow(rows * dist, 2) + pow(cols * dist, 2);
	hyp = sqrt(hyp);
	while (hyp < small_size)
	{
		dist += 1;
		hyp = pow(rows * dist, 2) + pow(cols * dist, 2);
		hyp = sqrt(hyp);
	}
	return (dist - 1);
}

t_map					init_map(t_file info)
{
	t_map				map;

	map.c = info.nb_line;
	map.r = info.len_line;
	map.cr = map.c * map.r;
	if (H < W)
		map.vec_dist = calc_dist(map.c, map.r, H);
	else
		map.vec_dist = calc_dist(map.c, map.r, W);
	map.axe_x = 0;
	map.axe_y = 0;
	map.axe_z = 0;
	return (map);
}

void					init_vec(t_map *map, char ***z_c)
{
	int					y;
	int					x;

	y = 0;
	x = 0;
	map->vec = (t_vec *)malloc(sizeof(*(map->vec)) * (map->cr));
	if (!map->vec)
		exit(EXIT_FAILURE);
	while (y < map->c)
	{
		x = 0;
		while (x < map->r)
		{
			map->vec[y * map->r + x].x = x * map->vec_dist;
			map->vec[y * map->r + x].y = y * map->vec_dist;
			map->vec[y * map->r + x].z = get_depth(z_c[y][x]);
			map->vec[y * map->r + x].color = get_color(z_c[y][x]);
			x++;
		}
		y++;
	}
}

int						main(int argc, char **argv)
{
	t_file				info;
	t_map				map;
	char				***tab_depth_color;

	tab_depth_color = NULL;
	if (argc == 1)
	{
		ft_putendl_fd("Usage : ./fdf <filename> [ case_size z_size ]", 2);
		exit(EXIT_FAILURE);
	}
	info = file_info(argv[1]);
	map = init_map(info);
	tab_depth_color = get_depth_color_str(argv[1], &map);
	init_vec(&map, tab_depth_color);

	/* free */

	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab_depth_color[i])
	{
		j = 0;
		while (tab_depth_color[i][j])
		{
			free(tab_depth_color[i][j]);
			tab_depth_color[i][j] = NULL;
			j++;
		}
		free(tab_depth_color[i]);
		tab_depth_color[i] = NULL;
		i++;
	}
	free(tab_depth_color);
	tab_depth_color = NULL;

	/* free */

	//vec_cpy = (t_vec *)ft_strnew(sizeof(*vec_cpy) * map.cr);
	//ft_memcpy(vec_cpy, map.vec, sizeof(*vec_cpy) * map.cr);

	draw(&map, NULL);
	return (0);
}
