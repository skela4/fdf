/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 05:47:23 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/04 15:50:02 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int                     count_line(char *file)
{
	int             fd;
	char    *line;
	int             lc;

	line = NULL;
	lc = 0;
	errno = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putendl(strerror(errno));
		display_error(76, "count_line");
	}
	while (get_next_line(fd, &line) > 0)
	{
		ft_strdel(&line);
		lc++;
	}
	return (lc);
}

int                     check_equal_line(char *file, int lcount)
{
	int             lc;
	int             fd;
	char    *line;

	line = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
		display_error(79, "open_fd");
	while (get_next_line(fd, &line) > 0)
	{
		lcount++;
		if (lcount > 1)
		{
			if (count_word(line) != lc)
			{
				ft_strdel(&line);
				ft_putendl("error line length, exiting");
				if (close(fd) == -1)
					ft_putendl("error");
				exit(EXIT_FAILURE);
			}
		}
		lc = count_word(line);
		ft_strdel(&line);
	}
	return (lc);
}
