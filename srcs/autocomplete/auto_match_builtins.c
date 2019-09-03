/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_match_builtins.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/10 20:15:06 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/02 17:02:55 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		auto_match_builtins(char *match, t_list **matchlst, int match_len)
{
	char	*builtin;

	builtin = NULL;
	if (ft_strnequ(match, "echo", match_len))
		builtin = "echo";
	else if (ft_strnequ(match, "exit", match_len))
		builtin = "exit";
	else if (ft_strnequ(match, "cd", match_len))
		builtin = "cd";
	else if (ft_strnequ(match, "export", match_len))
		builtin = "export";
	else if (ft_strnequ(match, "set", match_len))
		builtin = "set";
	else if (ft_strnequ(match, "unset", match_len))
		builtin = "unset";
	else if (ft_strnequ(match, "history", match_len))
		builtin = "history";
	else if (ft_strnequ(match, "type", match_len))
		builtin = "type";
	else if (ft_strnequ(match, "alias", match_len))
		builtin = "alias";
	else if (ft_strnequ(match, "unalias", match_len))
		builtin = "unalias";
	return (builtin == NULL ?
		FUNCT_FAILURE : auto_add_tolst(matchlst, builtin));
}
