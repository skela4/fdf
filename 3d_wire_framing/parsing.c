/
************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 22:02:34 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/06/30 06:39:51 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "example.h"

int		count_word(char	*str)
{
	int sep;  
	int wc;

	sep = 0;
	wc = 0;
	while (*str)  
	{  
		if (*str == ' ' || *str == '\n' || *str == '\t')  
			sep = 0;  
		else if (sep == 0)  
		{  
			sep = 1;  
			++wc;  
		}                                                
		++str;  
	}  
	return wc;  
}  

int		count_line(char *file)
{
	int		fd;
	char	*line;
	int		lines;

	line = NULL;
	lines = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		free(line);
		lines++;
	}
	close(fd);
	return (lines);
}

int		check_equal_line(char *file)
{
	int		fd;
	char	*line;
	int		cols;
	int		prev_cols;

	line = NULL;
	fd = open(file, O_RDONLY);
	get_next_line(fd, &line);
	prev_cols = count_word(line);
	free(line);
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		cols = count_word(line);
		if (prev_cols != cols)
		{
			free(line);
			line = NULL;
			close(fd);
			printf("error line length, exiting\n");
			exit(EXIT_FAILURE);
		}
		free(line);
		line = NULL;
	}
	close(fd);
	return (cols);
}

int			val(char c)
{ 
	int		value;

	value = 0;
	if (c >= '0' && c <= '9') 
		value = (int)c - '0'; 
	if (c >= 'A' && c <= 'F')
		value = (int)c - 'A' + 10; 
	if (c >= 'a' && c <= 'f')
		value = (int)c - 'a' + 10;
	return (value);	
}

int   ft_atoi_base(const char *str, int base)
{
	int len; 
	int power;
	int num;
	int i; 
	
	len = 0;
	power = 1;
	num = 0;
	i = 0;
	if (!str)
		return (0);
	if (str[0] == '0' && str[1] == 'x')
		str += 2;
	if (str[0] == '0' && str[1] == 'b')
		str += 2;
	if (str[0] == '0' && str[1] <= '7')
		str += 1;
	len = ft_strlen(str);
	i = len;
	while (--i >= 0)
	{
		if (val(str[i]) >= base)
			return (0);
		num += val(str[i]) * power;
		power = power * base;
	} 
	return (num); 
}

int		ft_detect_base(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	if (strlen(str) < 2)
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		return (10);
	}
	if (str[0] == '0' && str[1] == 'x')
		return (16);
	if (str[0] == '0' && str[1] == 'b')
		return (2);
	if (str[0] == '0' && str[1] <= '7')
		return (8);
	if (str[0] == '0' && (str[1] != 'x' || str[1] != 'b' || str[1] >= '8'))
		return (0);
	return (10);
}

void	get_z_and_color(char **tab, int tab_size, int *pos, t_point **pt)
{
	int		i;
	int		base;
	char	*sep;
	char	*cop;

	i = -1;
	base = 0;
	sep = NULL;
	cop = NULL;
	while (++i < tab_size)
	{
		printf("%s\n", tab[i]);
		if (!(sep = ft_strchr(tab[i], ',')))
			(base = ft_detect_base(tab[i])) ? (*pt)[(*pos)++].z = ft_atoi_base(tab[i], base) : 0;
		if (sep)
		{
			if (!(cop = ft_strsub(tab[i], 0, (ft_strlen(tab[i])) - ft_strlen(sep))))
				return;
			(base = ft_detect_base(cop)) ? (*pt)[*pos].z = ft_atoi_base(cop, base) : 0;
			(base = ft_detect_base(sep + 1)) ? (*pt)[(*pos)++].color = ft_atoi_base(sep + 1, base) : 0;
			free(cop);
			cop = NULL;
		}
	}
}

void	get_info_map(int fd, char *line, int cols, t_point **pt)
{
	char	**tab;
	int		pos;
	int		i;

	pos = 0;
	tab = NULL;
	while (get_next_line(fd, &line) > 0)
	{		
		tab = ft_strsplit(line, ' ');
		get_z_and_color(tab, cols, &pos, &(*pt));
		
		i = 0;
		while (i < cols)
		{
			free(tab[i]);
			tab[i++] = NULL;
		}
		free(tab);
		tab = NULL;
		free(line);
		line = NULL;
	}

}

t_point		*init_point(int cols, int rows)
{
	int		y;
	int		x;
	t_point	*pt;

	y = 0;
	x = 0;
	pt = NULL;
	if (!(pt = (t_point *)malloc(sizeof(*pt) * rows * cols)))
		return (NULL);

	while (y < cols)
	{
		x = 0;
		while (x < rows)
		{
			pt[y * rows + x].x = x * 50;
			pt[y * rows + x].y = y * 50;
			pt[y * rows + x].z = 0;
			pt[y * rows + x].color = 0;
			x++;
		}
		y++;
	}
	return (pt);
}

t_point		*create_point(int argc, char **argv, int cols, int rows)
{
	int		fd;

	t_point	*pt;
	pt = NULL;
	(void)argc;

	pt = init_point(cols, rows);

	fd = open(argv[1], O_RDONLY);

	get_info_map(fd, NULL, cols, &pt);

	/*int		i;
	i = 0;
	while (i < rows * cols)
	{
		printf("POSITION == %d\n\n", i);
		printf("x = %d y = %d z = %d color = %d", pt[i].x, pt[i].y, pt[i].z, pt[i].color);
		printf("\n");
		i++;
	}*/
	close(fd);

	return (pt);
}
