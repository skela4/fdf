/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 10:14:46 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/12 16:50:29 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				error(const char *file, char **line, int zero)
{
	int			fd;
	char		*err;

	errno = zero;
	err = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		err = strerror(errno);
		ft_putendl_fd(err, 2);
		return (-1);
	}
	return (fd);
}

int				word_count(char *str)
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

int				line_length(const char *file, int lc, int wc)
{
	char		*line;
	int			fd;
	int			ret;

	line = NULL;
	fd = error(file, &line, 0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		lc += 1;
		if (lc > 1)
		{
			if (wc != word_count(line))
			{
				ft_strdel(&line);
				return (-1);
			}
		}
		wc = word_count(line);
		ft_strdel(&line);
	}
	if (line)
		ft_strdel(&line);
	if (ret == -1)
		return (ret);
	return (wc);
}

int				line_count(const char *file)
{
	int			lc;
	char		*line;
	int			fd;
	int			ret;

	lc = 0;
	line = NULL;
	fd = error(file, &line, 0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		lc += 1;
		ft_strdel(&line);
	}
	if (line)
		ft_strdel(&line);
	if (ret == -1)
		return (ret);
	return (lc);
}

int				line_first(const char *file)
{
	int			wc;
	char		*line;
	int			fd;
	int			ret;

	wc = 0;
	line = NULL;
	fd = error(file, &line, 0);
	if (fd == -1)
		return (-1);
	if ((ret = get_next_line(fd, &line)) > 0)
	{
		wc = word_count(line);
		ft_strdel(&line);
	}
	if (line)
		ft_strdel(&line);
	if (ret == -1 || wc < 1)
		return (-1);
	return (wc);
}
