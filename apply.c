/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 06:58:41 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/13 07:16:21 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			apply_axe(t_map *map, t_vec *vec)
{
	int			i;

	i = 0;
	while (i < map->cr)
	{
		mat3_rot_x(map, map->axe_x, &(vec[i].x));
		mat3_rot_y(map, map->axe_y, &(vec[i].x));
		mat3_rot_z(map, map->axe_z, &(vec[i++].x));
	}
}

void			apply_zoom(t_map *map, t_vec *vec)
{
	int			i;

	i = 0;
	while (i < map->cr)
	{
		mat3_scale(map, map->zoom, &(vec[i].x));
		i++;
	}
}

void			apply_move(t_map *map, t_vec *vec)
{
	int			i;

	i = 0;
	while (i < map->cr)
	{
		mat3_move_x(map, map->move_x, &(vec[i].x));
		mat3_move_y(map, map->move_y, &(vec[i].x));
		i++;
	}
}
