/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_term_get_attributes.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/19 19:27:01 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/19 19:36:48 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		test_term_get_attributes(void)
{
	t_term	*term_p;

	if (term_get_attributes(STDIN_FILENO, NULL) != FUNCT_FAILURE)
		return (FUNCT_FAILURE);
	term_p = term_init_struct();
	if (term_get_attributes(STDIN_FILENO, term_p) != FUNCT_SUCCESS)
	{
		term_free_struct(&term_p);
		return (FUNCT_FAILURE);
	}
	if (term_get_attributes(STDOUT_FILENO, term_p) != FUNCT_SUCCESS)
	{
		term_free_struct(&term_p);
		return (FUNCT_FAILURE);
	}
	if (term_get_attributes(STDERR_FILENO, term_p) != FUNCT_SUCCESS)
	{
		term_free_struct(&term_p);
		return (FUNCT_FAILURE);
	}
	if (term_get_attributes(10101, term_p) != FUNCT_FAILURE)
	{
		term_free_struct(&term_p);
		return (FUNCT_FAILURE);
	}
	term_free_struct(&term_p);
	return (FUNCT_SUCCESS);
}
