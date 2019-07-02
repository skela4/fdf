/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exanple.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 01:19:41 by lmarques          #+#    #+#             */
/*   Updated: 2019/06/30 06:18:56 by aahizi-e         ###   ########.fr       */
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


# include "test/gnl/get_next_line.h"
# include "test/gnl/libft/libft.h"
# include "../../minilibx/mlx.h"

# define W 600
# define H 600

typedef	struct	s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
}				t_line;

typedef	struct	s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
	t_line	l;
	int		rows;
	int		cols;
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
	int			w;
	int			h;
	t_point		*pt;
	int 		cols;
	int			rows;
	int			angle;
}				t_mlx;

void	mlx_connect(t_mlx *mlx);
void	mlx_disconnect(t_mlx *mlx);
void	mlx_create_image(t_mlx *mlx);
void	mlx_clear_image(t_mlx *mlx);
void	mlx_close_image(t_mlx *mlx);
void	mlx_draw_image(t_mlx *mlx, t_point **pt, int cols, int rows);

int		hc_to_hi(char c);
int		count_word(const char *str);
int		count_line(char *file);
int		check_equal_line(char *file, int lcount);
int		atoi_base(const char *str, int base);
int		check_base(const char *str, const char *find);
int		detect_base(char *str);
void	get_z_and_color(char **tab, int tab_size, int *pos, t_point **pt);
int		get_info_map(t_point **pt, int cols, char *file);



int		display_error(int line_number, char *function_name);

t_point	*init_point(int cols, int rows);
t_point	*create_point(char *file);

void	put_pixel(t_mlx *mlx, int x, int y);

int		key_hook(int keycode, void *param);

void	rotate_Z(t_point **pt, int cols, int rows, int angle);
#endif
