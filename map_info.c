/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 06:36:20 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/06 06:32:17 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void            get_z_and_color(char **t, int t_size, int *pos, t_vec **vec)
{
	int			i;
	int			base;
	char		*s;
	char		*cop;

	i = -1;
	base = 0;
	s = NULL;
	cop = NULL;
	while (++i < t_size)
	{
		if (!(s = ft_strchr(t[i], ',')))
			if ((base = detect_base(t[i])))
				(*vec)[(*pos)++].z = atoi_base(t[i], base);
		if (s)
		{
			if (!(cop = ft_strsub(t[i], 0, (ft_strlen(t[i])) - ft_strlen(s))))
				return;
			if ((base = detect_base(cop)))
				(*vec)[*pos].z = atoi_base(cop, base);
			if ((base = detect_base(s + 1)))
				(*vec)[(*pos)++].c = atoi_base(s + 1, base);
			ft_strdel(&cop);
		}
	}
}

int                     get_info_map(t_vec **vec, int cols, char *file)
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
		get_z_and_color(tab, cols, &pos, &(*vec));
		i = 0;
		while (i < cols)
			ft_strdel(&tab[i++]);
		free(tab);
		tab = NULL;
		ft_strdel(&line);
	}
	return (1);
}
