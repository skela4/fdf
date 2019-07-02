/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 11:47:45 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/07/02 06:12:56 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"
#include <unistd.h>

static int			read_fd(int fd, char **remainder, char **s, char *buff)
{
	int				r;
	char			*tmp;

	while (!(*remainder = ft_strchr(*s, '\n'))
			&& (r = read(fd, buff, BUFF_SIZE)))
	{
		if (r < 0)
			return (-1);
		buff[r] = '\0';
		tmp = *s;
		if (!(*s = ft_strjoin(*s, buff)))
			return (1);
		ft_strdel(&tmp);
	}
	return (r);
}

static int			get_line(const int fd, char **line, char **s)
{
	int				ret;
	char			buffer[BUFF_SIZE + 1];
	char			*remain;
	char			*tmp;
	int				len;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if ((ret = read_fd(fd, &remain, &*s, buffer)) < 0)
		return (-1);
	if (!(len = ft_strlen(*s)) && !ret)
		return (0);
	if (!(*line = ft_strndup(*s, remain ? remain - *s : len)))
		return (-1);
	tmp = *s;
	if (!(*s = ft_strdup(remain ? remain + 1 : "")))
		return (-1);
	ft_strdel(&tmp);
	return (1);
}

static	t_list		*list_file_fd(t_list **file, int fd)
{
	t_list			*file_fd;

	file_fd = *file;
	while (file_fd)
	{
		if (file_fd->content_size == (size_t)fd)
			return (file_fd);
		file_fd = file_fd->next;
	}
	ft_lstadd(&*file, ft_lstnew("", fd));
	return (*file);
}

static	void		ft_listdel(t_list **alst)
{
	t_list  *head;
	t_list  *tmp;

	if (alst && del && (head = *alst))
	{
		while (*alst)
		{
			tmp = *alst;
			*alst = (*alst)->next;
			if (tmp->content)
				ft_strdel(&(tmp->content));
			free(tmp);
			tmp = NULL;
		}
		head = NULL;
	}
}


int					get_next_line(const int fd, char **line)
{
	static	t_list	*file;
	t_list			*current_file;
	int				ret;

	ft_putchar('X');
	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (!file)
		if (!(file = ft_lstnew("", fd)))
			return (-1);
	if (!(current_file = list_file_fd(&file, fd)))
		return (-1);
	if (!current_file->content || !(char *)current_file->content)
		if (!(current_file->content = ft_strnew(BUFF_SIZE)))
			return (-1);
	ret = get_line(fd, &*line, (char **)&current_file->content);
	ft_listdel(&current_file);
	return (ret);
}
