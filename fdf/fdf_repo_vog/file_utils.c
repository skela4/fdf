/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 05:47:23 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/02 06:58:12 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/libft/libft.h"
#include "gnl/get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int			display_error(int line_number, char *function_name)
{
	ft_putendl("Error");
	ft_putendl("function ");
	ft_putstr(function_name);
	ft_putendl(" ligne ");
	ft_putnbr(line_number);
	ft_putchar('\n');
	exit(EXIT_FAILURE);
}

void		open_fd(const char *file, int *fd)
{
	if ((*fd = open(file, O_RDONLY)) == -1)
		display_error(57, "open_fd");
}

void		close_fd(int fd)
{
	if (close(fd) == -1)
		display_error(63, " close_fd");
}

int			count_line(const char *file)
{
	int		fd;
	char	*line;
	int		lc;

	fd = 0;
	line = NULL;
	lc = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		display_error(76, "count_line");
	while (get_next_line(fd, &line) > 0)
	{
		ft_strdel(&line);
		lc++;
	}
	if (close(fd) == -1)
		display_error(45, "count_line");
	return (lc);
}

int			check_equal_line(const char *file, int fd, char *line)
{
	int		lc1;
	int		lc;

	open_fd(file, &fd);
	if (get_next_line(fd, &line) == -1)
		close_fd(fd);
	lc1 = count_word(line);
	ft_strdel(&line);
	while (get_next_line(fd, &line) > 0)
	{
		lc = count_word(line);
		if (lc1 != lc)
		{
			ft_strdel(&line);
			ft_putendl("error line length, exiting");
			close_fd(fd);
			exit(EXIT_FAILURE);
		}
		ft_strdel(&line);
	}
	close_fd(fd);
	return (lc1);
}
