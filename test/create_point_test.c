/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_point_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 03:16:01 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/02 07:04:28 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "gnl/get_next_line.h"
#include "gnl/libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

int             count_word(const char *str);
int             hc_to_hi(char c);
int             atoi_base(const char *str, int base);
int             detect_base(char *str);
int             check_base(char *str, char *find);
int             count_line(char *file);
int             check_equal_line(char *file, int lcount);

typedef struct	s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
}				t_line;

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			color;
	t_line		l;
}				t_point;

void			get_z_and_color(char **tab, int tab_size, int *pos, t_point **pt)
{
	int			i;
	int			base;
	char		*sep;
	char		*cop;

	i = -1;
	base = 0;
	sep = NULL;
	cop = NULL;
	while (++i < tab_size)
	{
		if (!(sep = ft_strchr(tab[i], ',')))
			(base = detect_base(tab[i])) ? (*pt)[(*pos)++].z = atoi_base(tab[i], base) : 0;
		if (sep)
		{
			if (!(cop = ft_strsub(tab[i], 0, (ft_strlen(tab[i])) - ft_strlen(sep))))
				return;
			(base = detect_base(cop)) ? (*pt)[*pos].z = atoi_base(cop, base) : 0;
			(base = detect_base(sep + 1)) ? (*pt)[(*pos)++].color = atoi_base(sep + 1, base) : 0;
			ft_strdel(&cop);
			//ft_strdel(&sep);
		}
	}
}

int				get_info_map(t_point **pt, int cols, char *file)
{
	int			fd;
	char		**tab;
	int			pos;
	int			i;
	char		*line;

	tab = NULL;
	pos	= 0;
	i = 0;
	line = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		get_z_and_color(tab, cols, &pos, &(*pt));
			i = 0;
		while (i < cols)
			ft_strdel(&tab[i++]);
		free(tab);
		tab = NULL;
		ft_strdel(&line);
	}
	return (1);
}

t_point			*init_point(int cols, int rows)
{
	int			y;
	int			x;
	t_point		*pt;

	y = 0;
	x = 0;
	pt = NULL;
	if (!(pt = (t_point *)malloc(sizeof(*pt) * (rows * cols))))
		return (NULL);
	while (y < cols)
	{
		x = 0;
		while (x < rows)
		{
			pt[y * rows + x].x = x;
			pt[y * rows + x].y = y;
			pt[y * rows + x].z = 0;
			pt[y * rows + x].color = 0;
			x++;
		}
		y++;
	}
	return (pt);
}

int				main(int argc, char **argv)
{
	int			i;
	int			cols;
	int			rows;
	t_point		*pt;

	i = 0;
	cols = 0;
	rows = 0;
	pt = NULL;
	if (argc != 2)
		return (0);

	cols = check_equal_line(argv[1], 0);
	rows = count_line(argv[1]);
	if (!(pt = init_point(cols, rows)))
	{
		ft_putendl("pt is null");
		exit(EXIT_FAILURE);
	}
	if (!(get_info_map(&pt, cols, argv[1])))
	{
		free(pt);
		pt = NULL;
	}
	while (i < cols * rows)
	{
		printf("y = %d x = %d color = %d\n", pt[i].y, pt[i].x, pt[i].color);
		i++;
	}
	free(pt);
	pt = NULL;

	return (0);
}
