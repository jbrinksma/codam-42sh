/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_prepare.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 10:10:56 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/27 11:41:53 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>

static t_vshdataterm	*term_return(t_vshdataterm *term_p, int return_value)
{
	if (return_value == FUNCT_FAILURE)
	{
		term_free_struct(&term_p);
		return (NULL);
	}
	return (term_p);
}

/*
**	TODO: Add specific alloc error for term_p
*/

t_vshdataterm			*term_prepare(t_envlst *envlst)
{
	t_vshdataterm	*term_p;

	term_p = term_init_struct();
	if (term_p == NULL)
		return (term_return(NULL, FUNCT_FAILURE));
	if (term_is_valid(envlst) == FUNCT_FAILURE)
		return (term_return(term_p, FUNCT_FAILURE));
	if (term_get_attributes(STDIN_FILENO, term_p) == FUNCT_FAILURE)
		return (term_return(term_p, FUNCT_FAILURE));
	if (term_set_attributes(term_p) == FUNCT_FAILURE)
		return (term_return(term_p, FUNCT_FAILURE));
	return (term_return(term_p, FUNCT_SUCCESS));
}
