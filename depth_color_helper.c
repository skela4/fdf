/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_color_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 08:53:23 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/08 13:59:17 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				get_depth(char *str)
{
	int			base;
	char		*depth;
	long		depth_number;
	char		*comma;

	base = 0;
	depth = NULL;
	depth_number = 0;
	comma = NULL;
	comma = ft_strchr(str, ',');
	if (!comma)
	{
		base = detect_base(str);
		depth_number = atoi_base(str, base);
		return (depth_number);
	}
	depth = ft_strndup(str, (size_t)(comma - str));
	if (!depth)
		exit(0);
	base = detect_base(depth);
	if (base)
		depth_number = atoi_base(depth, base);
	ft_strdel(&depth);
	return (depth_number);
}

#define HEX 6

int				format_color(char *color, size_t size, int base)
{
	char		*tmp;
	char		*new_color;
	long		color_number;
	char		*h;
	
	h = color;
	h += 2;
	size -= 2;
	color_number = 0;
	tmp = h;
	new_color = ft_strnew(HEX - size);
	ft_memset(new_color, '0', HEX - size);
	color = ft_strjoin(new_color, h);
	if (!color)
		exit(0);
	printf("new color = %s\n", color);
	color_number = atoi_base(color, base);

	printf("new color = %ld\n", color_number);
	return (color_number);
}

int				get_color(char *str)
{
	int			base;
	char		*color;
	long		color_number;
	char		*comma;

	base = 0;
	color = NULL;
	color_number = 0;
	comma = NULL;
	comma = ft_strchr(str, ',');
	if (!comma)
		return (0xFFFFFF);
	color = ft_strndup(comma + 1, ft_strlen(comma + 1));
	if (!color)
		exit(0);
	base = detect_base(color);
	if (base)
		color_number = atoi_base(color, base);
	//else if (base && ft_strlen(color) != 8)
	//{
	//	printf("color is == %s\n", color);
	//	color_number = format_color(color, ft_strlen(color), base);
	//}
	if (color_number == 0)
		color_number = 0xFFFFFF;
	ft_strdel(&color);
	return (color_number);
}

char			***get_depth_color_str(char *file, t_map *map)
{
	char		***depth_color;
	char		*line;
	int			ret;
	int			fd;
	int			i;

	depth_color = NULL;
	line = NULL;
	ret = 0;
	fd = 0;
	i = 0;
	depth_color = (char ***)malloc(sizeof(*depth_color) * (map->r + 1));
	if (!depth_color)
		return (NULL);
	fd = error_file(file, ret, &line, 0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		depth_color[i++] = ft_strsplit(line, ' ');
		ft_strdel(&line);
	}
	depth_color[i] = NULL;
	return (depth_color);
}
