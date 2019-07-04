/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 06:36:20 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/04 12:01:45 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void            get_z_and_color(char **tab, int tab_size, int *pos, t_point **pt)
{
	int             i;
	int             base;
	char    *sep;
	char    *cop;

	i = -1;
	base = 0;
	sep = NULL;
	cop = NULL;
	while (++i < tab_size)
	{
		if (!(sep = ft_strchr(tab[i], ',')))
		{
			if ((base = detect_base(tab[i])))
				(*pt)[(*pos)++].z = atoi_base(tab[i], base);
		}
		else if (sep)
		{
			if (!(cop = ft_strsub(tab[i], 0, (ft_strlen(tab[i])) - ft_strlen(sep))))
				return;
			if ((base = detect_base(cop)))
				(*pt)[*pos].z = atoi_base(cop, base);
			if ((base = detect_base(sep + 1)))
				(*pt)[(*pos)++].color = atoi_base(sep + 1, base);
			ft_strdel(&cop);
		}
	}
}

int                     get_info_map(t_point **pt, int cols, char *file)
{
	int             fd;
	char    **tab;
	int             pos;
	int             i;
	char    *line;

	tab = NULL;
	pos = 0;
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
