/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_term_init_struct.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 19:40:28 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/18 19:44:50 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		test_term_init_struct(void)
{
	t_term	*term_p;

	term_p = term_init_struct();
	if (!term_p)
		return (FUNCT_FAILURE);
	if (!term_p->termios_p)
		return (FUNCT_FAILURE);
	if (!term_p->old_termios_p)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
