/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_handle_matchlst.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/13 11:00:12 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/31 18:08:32 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		auto_handle_matchlst(t_vshdata *data, char *match, t_list **matchlst)
{
	int		lst_len;

	if (*matchlst == NULL)
	{
		ft_putchar('\a');
		return (AUTO_NO_MATCHES);
	}
	lst_len = ft_lstlen(*matchlst);
	if (lst_len == 1)
		return (auto_add_match_toline(
				match, (char *)(*matchlst)->content, data));
	else if (lst_len > 100)
		return (auto_big_lst(matchlst, lst_len));
	else
		return (auto_small_lst(match, matchlst, data));
}
