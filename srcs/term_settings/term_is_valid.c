/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_is_valid.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 18:16:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/23 13:39:54 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <term.h>

/*
**	Checks whether the termcaps database can be found for the current env_var
**	named 'TERM'.
*/

int		term_is_valid(t_envlst *envlst)
{
	char	*term_type;
	int		ret;

	term_type = env_getvalue("TERM", envlst);
	if (term_type == NULL)
	{
		ft_eprintf(E_TERM_NOT_SET);
		return (FUNCT_FAILURE);
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
		ft_eprintf(E_TERM_DB_NOT_F);
	if (ret == 0)
		ft_eprintf(E_TERM_NO_SUCH);
	if (ret == -1 || ret == 0)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
