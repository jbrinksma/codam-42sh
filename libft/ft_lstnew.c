/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-jong <tde-jong@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 11:29:39 by tde-jong       #+#    #+#                */
/*   Updated: 2019/04/29 18:02:19 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, size_t content_size)
{
	t_list *newlist;

	newlist = (t_list*)ft_memalloc(sizeof(t_list));
	if (newlist == NULL)
		return (NULL);
	if (content != NULL && content_size > 0)
	{
		newlist->content = (void*)ft_memalloc(content_size);
		if (newlist->content == NULL)
			return (NULL);
		ft_memcpy(newlist->content, content, content_size);
		newlist->content_size = content_size;
	}
	else
	{
		newlist->content = NULL;
		newlist->content_size = 0;
	}
	newlist->next = NULL;
	return (newlist);
}
