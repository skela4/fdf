/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 06:37:19 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/08 17:39:15 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"

# define W 1400
# define H 800
# define DEG(degrees) (degrees + M_PI / 180.0)
# define MAT_SIZE 9

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
	int			e1;
	int			e2;
}				t_line;

typedef struct	s_mat
{
	float		m11;
	float		m12;
	float		m13;
	float		m21;
	float		m22;
	float		m23;
	float		m31;
	float		m32;
	float		m33;
}				t_mat3;

typedef struct	s_vec
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_vec;

typedef struct	s_map
{
	int			c;
	int			r;
	int			cr;
	int			vec_dist;
	float		axe_x;
	float		axe_y;
	float		axe_z;
	t_vec		*vec;
}				t_map;

typedef struct	s_img
{
	int			size_l;
	int			bpp;
	int			endian;
	void		*img_ptr;
	int			*data;
}				t_img;

typedef struct	s_mlx
{
	t_img		img;
	t_map		*map;
	int			w;
	int			h;
	void		*mlx_ptr;
	void		*win_ptr;
}				t_mlx;

typedef struct	s_file
{
	int			nb_line;
	int			len_line;
	int			st_line;
}				t_file;

/*
**	file
*/

int				count_line(char *file);
int				first_line(char *file);
int				length_line(char *file);
int				count_word(char *str);
int				error_file(char *file, int ret, char **line, int err);

/*
**	base
*/

int				hc_to_hi(char c);
int				atoi_base(const char *str, int base);
int				check_base(const char *str, const char *find);
int				detect_base(char *str);

/*
**  depth_color
*/

int				get_depth(char *str);
int				get_color(char *str);
char			***get_depth_color_str(char *file, t_map *map);

/*
**  draw
*/

void			draw(t_map *map, t_vec *vec);
void			draw_map(t_mlx *mlx, t_map *map, t_vec *vec);
void			apply_axe(t_map *map, t_vec *vec);
void			send_line(t_mlx *mlx, t_map *map, t_vec *vec);
void			line(t_mlx *mlx, t_vec vec0, t_vec vec1);
void			put_pixel(t_mlx *mlx, int x, int y, int color);


/*
**  mlx
*/

void			loop(t_mlx *mlx, t_map *map);
int				key_press(int keycode, void *param);
void			free_map(t_mlx *map);

/*
**  matrice
*/

void			mat3_rot_x(t_map *map, float angle, int *vec);
void			mat3_rot_y(t_map *map, float angle, int *vec);
void			mat3_rot_z(t_map *map, float angle, int *vec);


#endif
