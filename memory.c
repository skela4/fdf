/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 00:38:45 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/13 09:27:25 by clboutry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			set_map_value(t_map *map, t_file *info)
{
	map->iso = 0;
	map->para = 0;
	map->axe_x = 0;
	map->axe_y = 0;
	map->axe_z = 0;
	map->zoom = 1.0;
	map->move_x = 0.0;
	map->move_y = 0.0;
	map->c = info->nb_line;
	map->r = info->len_line;
	map->cr = map->c * map->r;
	if (H < W)
		map->vec_dist = calc_dist(map->c, map->r, H);
	else if (H > W)
		map->vec_dist = calc_dist(map->c, map->r, W);
	else
		map->vec_dist = calc_dist(map->c, map->r, W);
}

t_vec			*copy_vec(t_map *map)
{
	t_vec		*vec_cpy;

	vec_cpy = (t_vec *)ft_strnew(sizeof(*vec_cpy) * map->cr);
	if (!vec_cpy)
	{
		free_all(map, 1);
		return (NULL);
	}
	ft_memcpy(vec_cpy, map->vec, sizeof(*vec_cpy) * map->cr);
	return (vec_cpy);
}

void			free_all(void *tf, int i)
{
	t_map		*map;

	if (!tf)
		return ;
	map = (t_map *)tf;
	if (i == 1)
	{
		if (map->tab_depth_color)
			free_tab3(&map->tab_depth_color, 0, map->c);
		if (map->vec)
		{
			free(map->vec);
			map->vec = NULL;
		}
	}
}

int				free_tab3(char ****str, int start, int end)
{
	char		***s;
	int			i;

	s = *str;
	i = 0;
	if (!str)
		return (0);
	while (start < end)
	{
		i = 0;
		while (s[start][i])
		{
			free(s[start][i]);
			s[start][i] = NULL;
			i++;
		}
		free(s[start]);
		s[start] = NULL;
		start++;
	}
	free(s);
	s = NULL;
	return (0);
}
