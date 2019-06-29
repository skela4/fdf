/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exanple.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 01:19:41 by lmarques          #+#    #+#             */
/*   Updated: 2019/06/27 02:40:21 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXAMPLE_H
# define EXAMPLE_H

# include <math.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "minilibx/mlx.h"

# define W 600
# define H 600

typedef	struct	s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	int			color;
}				t_line;

typedef struct	s_point
{
	int			*x;
	int			*y;
	int			*z;
	int			scale;
	int			cols;
	int			rows;
	t_line		l;
}				t_point;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_img		img;
	t_point		pt;
	int			w;
	int			h;
}				t_mlx;

void	mlx_connect(t_mlx *mlx);
void	mlx_disconnect(t_mlx *mlx);
void	mlx_create_image(t_mlx *mlx);
void	mlx_clear_image(t_mlx *mlx);
void	mlx_close_image(t_mlx *mlx);
void	mlx_draw_image(t_mlx *mlx);

#endif
