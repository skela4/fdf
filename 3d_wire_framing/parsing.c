/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 22:02:34 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/06/30 01:57:01 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "gnl/get_next_line.h"
#include "gnl/libft/libft.h"
#include <unistd.h>

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

typedef	 struct	s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}		t_point;


int             ft_natoi(const char *str)
{
	long    int             sign;
	long    int             nb;

	sign = 1;
	nb = 0;
	while (*str && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	if (*str && (*str == '-' || *str == '+'))
		sign = (*(str++) == '-') ? -1 : 1;
	while (*str && *str >= '0' && *str <= '9' && *str != ',')
		nb = nb * 10 + *(str++) - '0';
	return (nb * sign);
}

void	get_z_and_color(char **tab, int tab_size, int *pos, t_point **pt)
{
	int		i;
	char	*sep;

	i = 0;
	sep = NULL;
	while (i < tab_size)
	{
		if (!(sep = ft_strchr(tab[i], ',')))
		{
			(*pt)[*pos].z = ft_natoi(tab[i]);
			(*pt)[*pos].color = 0;
			(*pos)++;
		}
		if (sep)
		{
			(*pt)[*pos].z = ft_natoi(tab[i]);
			sep++;
			//ft_detect_base(sep);
			(*pos)++;
		}
		i++;
	}
}

void	get_info_map(int fd, char *line, int cols, t_point **pt)
{
	char	**tab;
	int		pos;

	pos = 0;
	tab = NULL;
	while (get_next_line(fd, &line) > 0)
	{		
		tab = ft_strsplit(line, ' ');
		get_z_and_color(tab, cols, &pos, &(*pt));
		free(line);
		line = NULL;
	}
}

int		main(int argc, char **argv)
{
	int		fd;
	int		cols;
	int		rows;
	t_point	*pt;

	(void)argc;
	cols = 0;
	rows = 0;
	pt = NULL;
	rows = count_line(argv[1]);
	cols = check_equal_line(argv[1]);
	//printf("%d %d \n", cols, rows);

	///////////////

	pt = (t_point *)malloc(sizeof(*pt) * rows * cols);	
	fd = open(argv[1], O_RDONLY);
	get_info_map(fd, NULL, cols, &pt);
	close(fd);
	int		i;
	i = 0;
	printf("\n");
	while (i < cols * rows)
	{
		printf("  z   value == %d\n", pt[i].z);
		printf("color value == %d\n", pt[i++].color);
	}
	return (0);
}
