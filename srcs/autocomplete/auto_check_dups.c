/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_check_dups.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/02 17:11:00 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/02 17:17:33 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool	auto_check_dups(t_list *matchlst, char *filename)
{
	while (matchlst != NULL)
	{
		if (ft_strequ(filename, matchlst->content) == true)
			return (true);
		matchlst = matchlst->next;
	}
	return (false);
}
