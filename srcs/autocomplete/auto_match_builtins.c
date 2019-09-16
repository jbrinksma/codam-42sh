/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_match_builtins.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/10 20:15:06 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/13 17:09:20 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	auto_match_builtins_continued(char *match, t_list **matchlst, int match_len)
{
	int ret;

	ret = FUNCT_FAILURE;
	if (ret != FUNCT_ERROR && ft_strnequ(match, "alias", match_len))
		ret = auto_add_tolst(matchlst, "alias");
	if (ret != FUNCT_ERROR && ft_strnequ(match, "unalias", match_len))
		ret = auto_add_tolst(matchlst, "unalias");
	if (ret != FUNCT_ERROR && ft_strnequ(match, "hash", match_len))
		ret = auto_add_tolst(matchlst, "hash");
	if (ret != FUNCT_ERROR && ft_strnequ(match, "fc", match_len))
		ret = auto_add_tolst(matchlst, "fc");
	return (ret);
}

int			auto_match_builtins(char *match, t_list **matchlst, int match_len)
{
	int ret;

	ret = FUNCT_FAILURE;
	if (ret != FUNCT_ERROR && ft_strnequ(match, "echo", match_len))
		ret = auto_add_tolst(matchlst, "echo");	
	if (ret != FUNCT_ERROR && ft_strnequ(match, "exit", match_len))
		ret = auto_add_tolst(matchlst, "exit");
	if (ret != FUNCT_ERROR && ft_strnequ(match, "cd", match_len))
		ret = auto_add_tolst(matchlst, "cd");
	if (ret != FUNCT_ERROR && ft_strnequ(match, "export", match_len))
		ret = auto_add_tolst(matchlst, "export");
	if (ret != FUNCT_ERROR && ft_strnequ(match, "set", match_len))
		ret = auto_add_tolst(matchlst, "set");
	if (ret != FUNCT_ERROR && ft_strnequ(match, "unset", match_len))
		ret = auto_add_tolst(matchlst, "unset");
	if (ret != FUNCT_ERROR && ft_strnequ(match, "history", match_len))
		ret = auto_add_tolst(matchlst, "history");
	if (ret != FUNCT_ERROR && ft_strnequ(match, "type", match_len))
		ret = auto_add_tolst(matchlst, "type");
	if (ret == FUNCT_ERROR)
		return (ret);
	return (auto_match_builtins_continued(match, matchlst, match_len));
}
