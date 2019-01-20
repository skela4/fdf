/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 09:53:21 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/01/20 15:39:18 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include "fdf.h"
#include "libft/libft.h"
#include "key_code.h"

int		key_hook(int key, void *param)
{
	t_fdf	*fdf;
	int		ret;

	fdf = (t_fdf *)param;

	if (key == MAIN_PAD_ESC)
		ret = mlx_destroy_window(fdf->mlx, fdf->win);
	else if (key == ARROW_UP)
		ret = mlx_string_put(fdf->mlx, fdf->win, fdf->size_x / 3, fdf->size_y / 3, 0xFF00FF, "aleksander");
	return (ret);
}

int		main(void)
{
	t_fdf	*fdf;
	int		ret;

	fdf->size_x = 600;
	fdf->size_y = 400;
	fdf->title = "mlx_42";
	if (!(fdf->mlx = mlx_init()))
		return (0);
	if (!(fdf->win = mlx_new_window(fdf->mlx, fdf->size_x, fdf->size_y, fdf->title)))
		return (0);
	ret = mlx_key_hook(fdf->win, &key_hook, &fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
