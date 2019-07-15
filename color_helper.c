/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 15:11:14 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/13 07:04:16 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			get_color(t_map *map, char *str, int base, long color_number)
{
	char	*color;
	char	*comma;

	color = NULL;
	comma = NULL;
	if (!str)
	{
		free_all(map, 1);
		exit(1);
	}
	if (!(comma = ft_strchr(str, ',')))
		return (0xFFFFFF);
	if (!(color = ft_strndup(comma + 1, ft_strlen(comma + 1))))
	{
		ft_putendl_fd("Error", 2);
		free_all(map, 1);
		exit(1);
	}
	if ((base = detect_base(color)))
		color_number = atoi_base(color, base);
	ft_strdel(&color);
	return (color_number);
}

int			get_depth(t_map *map, char *str, int base, long depth_number)
{
	char	*depth;
	char	*comma;

	depth = NULL;
	comma = NULL;
	if (!str)
	{
		free_all(map, 1);
		exit(1);
	}
	if (!(comma = ft_strchr(str, ',')))
	{
		base = detect_base(str);
		return ((depth_number = atoi_base(str, base)));
	}
	if (!(depth = ft_strndup(str, (size_t)(comma - str))))
	{
		free_all(map, 1);
		exit(1);
	}
	if ((base = detect_base(depth)))
		depth_number = atoi_base(depth, base);
	ft_strdel(&depth);
	return (depth_number);
}

char		***get_depth_color_s(const char *file, t_map *map, int fd, int ret)
{
	char	***depth_color;
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	if (!(depth_color = (char ***)malloc(sizeof(*depth_color) * (map->c + 1))))
		return (NULL);
	fd = error(file, &line, 0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!(depth_color[i++] = ft_strsplit(line, ' ')))
		{
			if (line)
				ft_strdel(&line);
			free_tab3(&depth_color, 0, i);
		}
		ft_strdel(&line);
	}
	if (line)
		ft_strdel(&line);
	if (ret == -1)
		free_tab3(&depth_color, 0, i);
	return (depth_color);
}
