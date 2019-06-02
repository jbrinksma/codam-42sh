/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 20:29:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/30 19:02:23 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	ft_printf alloc error handling
*/

int		main(int argc, char **argv)
{
	t_term	*term_p;
	char	**vshenviron;

	(void)argv;
	(void)argc;
	vshenviron = env_get_environ_cpy();
	term_p = term_prepare(vshenviron);
	history_get_file_content();
	/* if !term_p or history failed: send appropriate error message/log */
	if (term_p == NULL)
		return (EXIT_FAILURE);
	shell_start();
	if (term_reset(term_p) == FUNCT_FAILURE)
		return (EXIT_FAILURE);
	term_free_struct(&term_p);
	ft_freearray(&vshenviron);
	return (EXIT_SUCCESS);
}
