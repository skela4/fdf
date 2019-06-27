/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 03:51:42 by lmarques          #+#    #+#             */
/*   Updated: 2019/06/27 05:21:03 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_num(char *line)
{
	char	*h;
	char	*t;
	char	*nb;
	int		num;

	nb = NULL;
	h = line;
	t = h;
	while (*line && *line == ' ')
		line++;
	while (*t && *t >= '0' && *t <= '9')
		t++;
	nb = ft_strsub(h, 0, t - h);
	num = ft_atoi(nb);
	free(nb);
	return (num);
}

t_point		**ft_create_2d_tab(int fd, char *line)
{
	int		i;
	char	*t;
	t_point	**pt;

	i = -1;
	pt = NULL;
	if (!(pt = (t_point **)malloc(sizeof(t_point*) * (11 * 19))))
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		t = line;
		while (*t)
		{
			pt[++i] = (t_point *)malloc(sizeof(t_point));
			if (!pt[i])
				return (NULL);
			pt[i]->z = get_num(t);
			while (*t && *t >= '0' && *t <= '9')
				t++;
			while (*t && !(*t >= '0' && *t <= '9'))
				t++;
		}
		free(line);
	}
	return (pt);
}
