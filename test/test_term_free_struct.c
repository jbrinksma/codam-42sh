/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_term_free_struct.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/19 19:13:07 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/19 19:21:40 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		test_term_free_struct(void)
{
	t_term	*term_p;

	term_p = term_init_struct();
	term_free_struct(&term_p);
	if (term_p != NULL)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
