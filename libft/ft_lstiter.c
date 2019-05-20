/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstitter.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 16:03:05 by mavan-he       #+#    #+#                */
/*   Updated: 2019/05/16 16:03:46 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (lst == NULL || f == NULL)
		return ;
	f(lst);
	ft_lstiter(lst->next, f);
}
