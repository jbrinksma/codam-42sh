/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_term_is_valid.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/19 18:33:51 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/19 18:38:35 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		test_term_is_valid(void)
{
	char *test1;
	char *test2;

	test1 = "TERM=non_valid_term";
	test2 = "TERM=vt100";
	if (term_is_valid(&test1) != FUNCT_FAILURE)
		return (FUNCT_FAILURE);
	if (term_is_valid(&test2) != FUNCT_SUCCESS)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
