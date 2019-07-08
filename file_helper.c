/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 02:48:39 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/08 11:20:52 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				error_file(char *file, int ret, char **line, int err)
{
	int			fd;

	fd = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1 || ret == -1 || err == -1)
	{
		if (line && (*line))
			ft_strdel(&(*line));
		if (err == -1)
			ft_putendl_fd("Error line length exiting", 2);
		else
			ft_putendl_fd("Error", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int				count_word(char *str)
{
	int			wc;
	int			sep;

	wc = 0;
	sep = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if ((*str >= 9 && *str <= 13) || *str == 32)
			sep = 0;
		else if (sep == 0)
		{
			sep = 1;
			wc += 1;
		}
		str++;
	}
	return (wc);
}

int				count_line(char *file)
{
	int			fd;
	int			ret;
	int			lc;
	char		*line;

	ret = 0;
	lc = 0;
	line = NULL;
	fd = error_file(file, ret, &line, 0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		error_file(file, ret, &line, 0);
		lc += 1;
		ft_strdel(&line);
	}
	return (lc);
}

int				first_line(char *file)
{
	int			fd;
	int			ret;
	int			wc;
	char		*line;

	wc = 0;
	ret = 0;
	line = NULL;
	fd = error_file(file, ret, &line, 0);
	if ((ret = get_next_line(fd, &line)) > 0)
	{
		error_file(file, ret, &line, 0);
		wc = count_word(line);
		ft_strdel(&line);
	}
	return (wc);
}

int				length_line(char *file)
{
	int			fd;
	int			ret;
	int			lc;
	int			wc;
	char		*line;

	fd = 0;
	lc = 0;
	wc = 0;
	ret = 0;
	line = NULL;
	fd = error_file(file, ret, &line, 0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		error_file(file, ret, &line, 0);
		lc += 1;
		if (lc > 1)
		{
			if (wc != count_word(line))
				error_file(file, ret, &line, -1);
		}
		wc = count_word(line);
		ft_strdel(&line);
	}
	return (wc);
}
