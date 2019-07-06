/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 06:37:19 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/06 07:12:50 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"

# define W 1600
# define H 1600
# define DEGTORAD(degrees) (degrees * M_PI / 180.0)
# define RADTODEG(radians) (radians * 180.0 / M_PI)

typedef struct	s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
}				t_line;

typedef struct	s_vec
{
	int			x;
	int			y;
	int			z;
	int			c;
}				t_vec;

typedef struct	s_map
{
	int			c;
	int			r;
	int			total;
	t_vec		*vec;
}				t_map;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct  s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_img		img;
	int			w;
	int			h;
}				t_mlx;

void    mlx_connect(t_mlx *mlx);
void    mlx_disconnect(t_mlx *mlx);
void    mlx_create_image(t_mlx *mlx);
void    mlx_clear_image(t_mlx *mlx);
void    mlx_close_image(t_mlx *mlx);
void    mlx_draw_image(t_mlx *mlx, t_vec *vec);

int		hc_to_hi(char c);
int		count_word(const char *str);
int		count_line(char *file);
int		check_equal_line(char *file, int lcount);
int		atoi_base(const char *str, int base);
int		check_base(const char *str, const char *find);
int		detect_base(char *str);
int		display_error(int line_number, char *function_name);

void	get_z_and_color(char **t, int t_size, int *pos, t_vec **vec);
int		get_info_map(t_vec **vec, int cols, char *file);

t_vec	*init_vec(int cols, int rows);
t_vec	*create_vec(char *file, t_map *map);

void	draw_map(t_mlx *mlx, t_map *map);

#endif
