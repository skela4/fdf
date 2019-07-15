/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 07:01:05 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/13 07:57:38 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			transform_fig(t_mlx *mlx, t_vec *vec0, t_vec *vec1)
{
	vec0->xp0 = vec0->x;
	vec0->yp0 = vec0->y;
	vec0->zp0 = vec0->z;
	vec1->xp1 = vec1->x;
	vec1->yp1 = vec1->y;
	vec1->zp1 = vec1->z;
	if (mlx->map->iso == 1)
	{
		vec0->x = (int)(0.71 * (vec0->xp0 - vec0->yp0));
		vec0->y = (int)(-(-0.41 * (vec0->xp0 + vec0->yp0)) + 0.82 * -vec0->zp0);
		vec1->x = (int)(0.71 * (vec1->xp1 - vec1->yp1));
		vec1->y = (int)(-(-0.41 * (vec1->xp1 + vec1->yp1)) + 0.82 * -vec1->zp1);
	}
	else if (mlx->map->para == 1)
	{
		vec0->x = (int)(vec0->xp0 + 0.44 * vec0->zp0);
		vec0->y = (int)(vec0->yp0 + 0.89 * vec0->zp0);
		vec1->x = (int)(vec1->xp1 + 0.44 * vec1->zp1);
		vec1->y = (int)(vec1->yp1 + 0.89 * vec1->zp1);
	}
}
