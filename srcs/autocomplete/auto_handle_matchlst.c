/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_handle_matchlst.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/13 11:00:12 by mavan-he       #+#    #+#                */
/*   Updated: 2019/11/06 13:18:38 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	If no matches have been found, an error sound occurs
**	We return NO_MATCHES so that there is no newline printed
**	When there is only one match it is added to line
**	When there are less than 100 matches we display them
**	otherwise we give a 'yes or no' prompt whether to print the lst or not
*/

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
		return (auto_add_match_to_line(
				match, (char *)(*matchlst)->content, data));
	else if (lst_len > 100)
		return (auto_big_lst(matchlst, lst_len));
	else
		return (auto_small_lst(match, matchlst, data));
}
