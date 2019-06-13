/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstaddback.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@jbrinksm.codam.nl>        +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 18:35:11 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/06/07 18:37:05 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void		env_lstaddback(t_envlst **lst, t_envlst *new)
{
	if (lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else if ((*lst)->next == NULL)
		(*lst)->next = new;
	else
		env_lstaddback(&(*lst)->next, new);
}
