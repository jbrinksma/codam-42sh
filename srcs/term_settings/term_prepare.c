/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_prepare.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 10:10:56 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/02 09:48:42 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>

static t_term	*term_return(t_term *term_p, int return_value)
{
	if (return_value == FUNCT_FAILURE)
	{
		term_free_struct(&term_p);
		return (NULL);
	}
	return (term_p);
}

t_term			*term_prepare(t_envlst *envlst)
{
	t_term	*term_p;

	term_p = term_init_struct();
	/* Add specific alloc error here */
	if (term_p == NULL)
		return (term_return(NULL, FUNCT_FAILURE));
	g_state->termios_p = term_p->termios_p;
	if (term_is_valid(envlst) == FUNCT_FAILURE)
		return (term_return(term_p, FUNCT_FAILURE));
	if (term_get_attributes(STDIN_FILENO, term_p) == FUNCT_FAILURE)
		return (term_return(term_p, FUNCT_FAILURE));
	if (term_set_attributes(term_p) == FUNCT_FAILURE)
		return (term_return(term_p, FUNCT_FAILURE));
	return (term_return(term_p, FUNCT_SUCCESS));
}
