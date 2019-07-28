/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_alias_lstdel.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/24 21:39:17 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/24 21:46:36 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	builtin_alias_delnode(t_aliaslst **node)
{
	ft_strdel(&(*node)->var);
	ft_memdel((void**)node);
}

void	builtin_alias_lstdel(t_aliaslst **lst)
{
	if (lst == NULL || *lst == NULL)
		return ;
	if ((*lst)->next != NULL)
		builtin_alias_lstdel(&(*lst)->next);
	builtin_alias_delnode(lst);
}
