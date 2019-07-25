/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 20:29:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/25 15:56:59 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	ft_printf alloc error handling
*/

int		main(int argc, char **argv)
{
	t_term		*term_p;
	t_vshdata	vshdata;

	(void)argv;
	(void)argc;
	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	if (g_state == NULL)
		return (EXIT_FAILURE);
	vshdata.envlst = env_getlst();
	if (vshdata.envlst == NULL)
		return (EXIT_FAILURE);
	term_p = term_prepare(vshdata.envlst);
	history_get_file_content();
	/* if !term_p, history or envlst failed: send appropriate error message/log */
	if (term_p == NULL)
		return (EXIT_FAILURE);
	shell_start(&vshdata);
	if (term_reset(term_p) == FUNCT_FAILURE)
		return (EXIT_FAILURE);
	term_free_struct(&term_p);
	return (EXIT_SUCCESS);
}
