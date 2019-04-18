/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:37:32 by omulder        #+#    #+#                */
/*   Updated: 2019/04/18 22:06:27 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		test_prompt(void)
{
	shell_display_prompt();
	return (FUNCT_SUCCESS);
}

int		main(void)
{
	if (test_prompt() == FUNCT_FAILURE)
		return (EXIT_FAILURE);
	if (test_term_init_struct() == FUNCT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
