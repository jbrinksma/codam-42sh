/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_lstdel.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 18:35:20 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/06/07 18:37:15 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void		env_lstdel(t_envlst **envlst)
{
	if (envlst == NULL || *envlst == NULL)
		return ;
	if ((*envlst)->next != NULL)
		env_lstdel(&(*envlst)->next);
	ft_strdel(&(*envlst)->var);
	ft_memdel((void**)envlst);
}
