/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 06:37:19 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/13 09:30:53 by clboutry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"

# define W 1400
# define H 800
# define DEG_TO_RAD(degrees) (degrees * M_PI / 180.0)

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
	int			xp0;
	int			yp0;
	int			zp0;
	int			xp1;
	int			yp1;
	int			zp1;
	int			color;
}				t_vec;

typedef struct	s_map
{
	long		c;
	long		r;
	long		cr;
	long		vec_dist;
	int			set_axe;
	float		axe_x;
	float		axe_y;
	float		axe_z;
	float		move_x;
	float		move_y;
	float		zoom;
	t_vec		*vec;
	int			iso;
	int			para;
	char		***tab_depth_color;
}				t_map;

typedef struct	s_img
{
	int			size_l;
	int			bpp;
	int			endian;
	void		*img_ptr;
	int			*data;
}				t_img;

typedef struct	s_btn
{
	int			x;
	int			y;
	int			pressed;
	int			released;
	int			notifying;
}				t_btn;

typedef struct	s_mlx
{
	t_img		img;
	t_map		*map;
	t_btn		btn;
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

int				line_count(const char *file);
int				line_first(const char *file);
int				line_length(const char *file, int lc, int wc);
int				word_count(char *str);
int				error(const char *file, char **line, int zero);
void			set_map_value(t_map *map, t_file *info);
int				calc_dist(int cols, int rows, int smallest_size);

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

int				get_depth(t_map *map, char *str, int base, long depth_number);
int				get_color(t_map *map, char *str, int base, long color_number);
char			***get_depth_color_s(const char *file, t_map *map,
				int fd, int ret);

/*
**  draw
*/

int				create_map(t_map *map);
void			draw_map(t_mlx *mlx, t_map *map, t_vec *vec);
void			apply_axe(t_map *map, t_vec *vec);
void			apply_move(t_map *map, t_vec *vec);
void			apply_zoom(t_map *map, t_vec *vec);
void			draw_line(t_mlx *mlx, t_map *map, t_vec *vec);
void			line(t_mlx *mlx, t_vec vec0, t_vec vec1);
void			put_pixel(t_mlx *mlx, int x, int y, int color);

/*
**  projection
*/

void			transform_fig(t_mlx *mlx, t_vec *vec0, t_vec *vec1);

/*
**  mlx
*/

int				mlx_connect(t_mlx *mlx);
void			mlx_hook_function(t_mlx *mlx);
void			rotation_key(t_mlx *mlx, int key);
void			projection_key(t_mlx *mlx, int key);
int				key_press(int keycode, void *param);
int				close_program(void *param);
void			free_map(t_mlx *map);

/*
**  matrice
*/

void			mat3_scale(t_map *map, float angle, int *vec);
void			mat3_move_x(t_map *map, float angle, int *vec);
void			mat3_move_y(t_map *map, float angle, int *vec);
void			mat3_rot_x(t_map *map, float angle, int *vec);
void			mat3_rot_y(t_map *map, float angle, int *vec);
void			mat3_rot_z(t_map *map, float angle, int *vec);

/*
**	copy
*/

t_vec			*copy_vec(t_map *map);

/*
**  free
*/

int				close_window(void *param);
int				free_tab3(char ****s, int start, int end);
void			free_all(void *tf, int i);

#endif
