/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:37:32 by omulder        #+#    #+#                */
/*   Updated: 2019/04/23 15:00:05 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		main(void)
{
	if (test_prompt() == FUNCT_FAILURE)
		return (EXIT_FAILURE);
	if (test_check_for_single_equalsign() == FUNCT_FAILURE)
		return (EXIT_FAILURE);
	if (test_free_and_return_null() == FUNCT_FAILURE)
		return (EXIT_FAILURE);
	if (test_get_environ_cpy() == FUNCT_FAILURE)
		return (EXIT_FAILURE);
	if (test_param_to_env() == FUNCT_FAILURE)
		return (EXIT_FAILURE);
	if (test_term_is_valid() == FUNCT_FAILURE)
		return (EXIT_FAILURE);
	if (test_term_init_struct() == FUNCT_FAILURE)
		return (EXIT_FAILURE);
	if (test_term_free_struct() == FUNCT_FAILURE)
		return (EXIT_FAILURE);
	if (test_term_get_attributes() == FUNCT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
