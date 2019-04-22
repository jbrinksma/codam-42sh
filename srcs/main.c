/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 20:29:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/19 20:33:57 by jbrinksm      ########   odam.nl         */
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
	vshenviron = get_environ_cpy();
	term_p = term_prepare(vshenviron);
	/* if !term_p: send appropriate error message/log */
	if (term_p == NULL)
		return (EXIT_FAILURE);
	shell_start();
	term_reset(term_p);
	term_free_struct(&term_p);
	ft_freearray(&vshenviron);
}
