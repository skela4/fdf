/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahizi-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 04:47:57 by aahizi-e          #+#    #+#             */
/*   Updated: 2019/01/17 16:52:00 by aahizi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_lstadd_link(t_list **list, void *content, size_t content_size)
{
	t_list	*newlst;

	if (!(newlst = (t_list *)malloc(sizeof(t_list))))
		return (0);
	if (content)
	{
		if (!(newlst->content = malloc(content_size)))
			return (0);
		ft_memcpy(newlst->content, content, content_size);
		newlst->content_size = content_size;
		newlst->next = *list;
	}
	else
	{
		newlst->content = NULL;
		newlst->content_size = 0;
		newlst->next = NULL;
	}
	*list = newlst;
	return (1);
}

t_list		*ft_lstnew(void	const *content, size_t content_size)
{
	t_list	*lst;

	lst = NULL;
	ft_lstadd_link(&lst, (void *)content, content_size);
	return (lst);
}
