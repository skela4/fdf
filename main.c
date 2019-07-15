/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 10:14:46 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/13 09:41:39 by clboutry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int		file_info(t_file *info, const char *file)
{
	if (error(file, NULL, 0) == -1)
		return (-1);
	if ((info->st_line = line_first(file)) == -1)
	{
		ft_putendl_fd("No data found", 2);
		return (-1);
	}
	if ((info->nb_line = line_count(file)) == -1)
	{
		ft_putendl_fd("No data found", 2);
		return (-1);
	}
	if ((info->len_line = line_length(file, 0, 0)) == -1)
	{
		ft_putendl_fd("Error line length exiting", 2);
		return (-1);
	}
	return (0);
}

int				calc_dist(int cols, int rows, int smallest_size)
{
	int			dist;
	int			hyp;

	dist = 1;
	hyp = sqrt(pow(rows * dist, 2) + pow(cols * dist, 2));
	while (hyp < smallest_size)
	{
		dist += 1;
		hyp = sqrt(pow(rows * dist, 2) + pow(cols * dist, 2));
	}
	return (dist - 1);
}

static	t_vec	*set_vec(t_map *map, char ****z_c)
{
	int			y;
	int			x;

	y = 0;
	x = 0;
	map->vec = (t_vec *)malloc(sizeof(*(map->vec)) * (map->cr));
	if (!map->vec)
	{
		free_tab3(&map->tab_depth_color, 0, map->c);
		return (NULL);
	}
	while (y < map->c)
	{
		x = 0;
		while (x < map->r)
		{
			map->vec[y * map->r + x].x = x * map->vec_dist;
			map->vec[y * map->r + x].y = y * map->vec_dist;
			map->vec[y * map->r + x].z = get_depth(map, (*z_c)[y][x], 0, 0);
			map->vec[y * map->r + x].color = get_color(map, (*z_c)[y][x], 0, 0);
			x++;
		}
		y++;
	}
	return (map->vec);
}

static	int		set_map(t_map *map, t_file *info, const char *file)
{
	char	***s;

	set_map_value(map, info);
	map->tab_depth_color = get_depth_color_s(file, map, 0, 0);
	if (!map->tab_depth_color)
		return (-1);
	if (!(map->vec = set_vec(map, &map->tab_depth_color)))
	{
		free_tab3(&map->tab_depth_color, 0, map->c);
		return (-1);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_file		info;
	t_map		map;

	map.vec = NULL;
	map.tab_depth_color = NULL;
	if (argc != 2)
	{
		ft_putendl_fd("Usage : ./fdf <path_to_map>", 2);
		return (1);
	}
	if (file_info(&info, argv[1]) == -1)
		return (errno);
	if (set_map(&map, &info, argv[1]) == -1)
		return (1);
	create_map(&map);
	return (0);
}
