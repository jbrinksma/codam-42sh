/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_str_to_lst.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/05 12:49:04 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/05 12:49:19 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Be sure that the t_list* is initialized to NULL if it doesnt exist yet.
*/

void	add_str_to_lst(char *str, t_list **lst)
{
	t_list	*probe;

	if (*lst == NULL)
		*lst = ft_lstnew(str, ft_strlen(str) + 1);
	else
	{
		probe = *lst;
		while (probe->next != NULL)
			probe = probe->next;
		probe->next = ft_lstnew(str, ft_strlen(str) + 1);
	}
}
