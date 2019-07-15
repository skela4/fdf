/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:16:30 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/13 07:57:45 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void					mat3_scale(t_map *map, float scale, int *vec)
{
	int					x;
	int					y;
	int					z;

	x = vec[0];
	y = vec[1];
	z = vec[2];
	vec[0] = x * scale;
	vec[1] = y * scale;
	vec[2] = z * scale;
}

void					mat3_move_x(t_map *map, float angle, int *vec)
{
	int					x;
	int					y;
	int					z;

	x = vec[0];
	y = vec[1];
	z = vec[2];
	vec[0] = x + angle;
	vec[2] = z + angle;
}

void					mat3_move_y(t_map *map, float angle, int *vec)
{
	int					x;
	int					y;
	int					z;

	x = vec[0];
	y = vec[1];
	z = vec[2];
	vec[1] = y + angle;
	vec[2] = z + angle;
}
