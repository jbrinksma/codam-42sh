/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_get_varlst.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/11 15:38:10 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/05 15:56:44 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	auto_get_varlst finds all matches for match in envlst
*/

int		auto_get_varlst(char *match, int match_len, t_envlst *envlst,
		t_list **matchlst)
{
	char *equal;
	char *new_match;

	if (envlst == NULL)
		return (FUNCT_SUCCESS);
	if (ft_strnequ(match, envlst->var, match_len) == true)
	{
		equal = ft_strchr(envlst->var, '=');
		if (equal != NULL)
			new_match = ft_strndup(envlst->var, equal - envlst->var);
		else
			new_match = ft_strdup(envlst->var);
		if (new_match == NULL ||
			auto_add_tolst(matchlst, new_match) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		ft_strdel(&new_match);
	}
	return (auto_get_varlst(match, match_len, envlst->next, matchlst));
}
