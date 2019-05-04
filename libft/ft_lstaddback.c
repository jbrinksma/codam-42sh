/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstaddback.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-jong <tde-jong@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 13:03:09 by tde-jong       #+#    #+#                */
/*   Updated: 2019/05/04 16:46:04 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddback(t_list *alst, t_list *new)
{
	if (alst->next != NULL)
		ft_lstaddback(alst->next, new);
	else
		alst->next = new;
}
