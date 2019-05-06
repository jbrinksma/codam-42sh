/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_lst_to_lst.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/05 12:52:11 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/05 12:52:22 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Function to add a lst as a content for another list.
**
**	Make sure that the lst_lst pointer is initialized to NULL if it doesnt exist
**	yet.
*/

void	add_lst_to_lst(t_list *lst_content, t_list **lst_lst)
{
	t_list	*probe;

	if (*lst_lst == NULL)
	{
		*lst_lst = ft_lstnew(NULL, 0);
		(*lst_lst)->content = lst_content;
	}
	else
	{
		probe = *lst_lst;
		while (probe->next != NULL)
			probe = probe->next;
		probe->next = ft_lstnew(NULL, 0);
		probe->next->content = lst_content;
	}
}
