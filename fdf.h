/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exanple.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 01:19:41 by lmarques          #+#    #+#             */
/*   Updated: 2019/06/27 05:19:02 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdio.h>
# include "./minilibx_macos/mlx.h"

# define EXIT_FAILURE 0
# define EXIT_SUCCESS 1
# define WIN_WIDTH 600
# define WIN_HEIGHT 600

typedef struct	s_img
{
	void		*ptr;
	int			*data;
	int			size;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
	t_img		img;
}				t_mlx;

static const int data[11][10] = 
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 10, 10, 0, 0, 10, 10, 0, 0},
	{0, 0, 10, 10, 0, 0, 10, 10, 0, 0},
	{0, 0, 10, 10, 0, 0, 10, 10, 0, 0},
	{0, 0, 10, 10, 10, 10, 10, 10, 0, 0},
	{0, 0, 0, 10, 10, 10, 10, 10, 0, 0},
	{0, 0, 0, 0, 0, 0, 10, 10, 0, 0},
	{0, 0, 0, 0, 0, 0, 10, 10, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

#endif
