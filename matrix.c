/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:16:30 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/08 17:39:31 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			mat3_rot_x(t_map *map, float angle, int *vec)
{
	int			y;
	int			z;
	float		*rotx;
	static		t_mat3  rx = {0};

	y = vec[1];
	z = vec[2];

	rotx = &(rx.m11);
	rotx[0] = 1;
	rotx[4] = cos(angle);
	rotx[5] = -sin(angle);
	rotx[7] = sin(angle);
	rotx[8] = cos(angle);
	vec[1] = (y - (map->c * map->vec_dist) / 2) * rotx[4] + z * rotx[5] * 5;
	vec[2] = (y - (map->c * map->vec_dist) / 2) * rotx[7] + z * rotx[8] * 5;
}


void			mat3_rot_y(t_map *map, float angle, int *vec)
{
	int			x;
	int			z;
	float		*roty;
	static		t_mat3  ry = {0};

	x = vec[0];
	z = vec[2];

	roty = &(ry.m11);
	roty[0] = cos(angle);
	roty[2] = sin(angle);
	roty[4] = 1;
	roty[6] = -sin(angle);
	roty[8] = cos(angle);
	vec[0] = (x - (map->r * map->vec_dist) / 2) * roty[0] + z * roty[2];
	vec[2] = (x - (map->r * map->vec_dist) / 2) * roty[6] + z * roty[8];
}

void			mat3_rot_z(t_map *map, float angle, int *vec)
{
	int			x;
	int			y;
	float		*rotz;
	static		t_mat3  rz = {0};

	x = vec[0];
	y = vec[1];

	rotz = &(rz.m11);
	rotz[0] = cos(angle);
	rotz[1] = -sin(angle);
	rotz[3] = sin(angle);
	rotz[4] = cos(angle);
	rotz[8] = 1;
	vec[0] = x * rotz[0] + y * rotz[1];
	vec[1] = x * rotz[3] + y * rotz[4];
}
