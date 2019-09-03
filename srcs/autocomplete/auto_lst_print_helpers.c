/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_print_matches.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/15 10:22:31 by omulder        #+#    #+#                */
/*   Updated: 2019/08/15 10:42:24 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	auto_swap_lstitem(t_list **flst, t_list *smal, t_list *prev)
{
	prev->next = smal->next;
	smal->next = *flst;
	*flst = smal;
}

void	auto_sort_n(t_list **matchlst)
{
	t_list	*ptr;
	t_list	*prev;
	t_list	*smallest;
	t_list	*prevsmal;

	smallest = *matchlst;
	ptr = smallest->next;
	prev = *matchlst;
	while (ptr != NULL)
	{
		if (ft_strcmp(smallest->content, ptr->content) > 0)
		{
			prevsmal = prev;
			smallest = ptr;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	if (smallest != *matchlst)
		auto_swap_lstitem(matchlst, smallest, prevsmal);
	if ((*matchlst)->next != NULL)
		auto_sort_n(&(*matchlst)->next);
}

int		auto_lst_count(t_list *lst)
{
	if (lst == NULL)
		return (0);
	return (1 + auto_lst_count(lst->next));
}

int		auto_lenname(t_list *matchlst, int length)
{
	int len;

	if (matchlst != NULL)
	{
		len = ft_strlen(matchlst->content);
		if (length > len)
			len = length;
		if (matchlst->next != NULL)
			return (auto_lenname(matchlst->next, len));
		return (len);
	}
	return (length);
}
