/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 20:29:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/30 16:36:20 by jbrinksm      ########   odam.nl         */
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
	g_state->exit_code = EXIT_SUCCESS;
	if (shell_init_vshdata(&vshdata) == FUNCT_ERROR)
		return (EXIT_FAILURE);
	term_p = term_prepare(vshdata.envlst);
	if (g_state == NULL || term_p == NULL)
		return (EXIT_FAILURE);
	if (redir_save_stdfds(&vshdata) == FUNCT_ERROR)
		return (EXIT_FAILURE);
	shell_start(&vshdata);
	if (term_reset(term_p) == FUNCT_FAILURE)
		return (EXIT_FAILURE);
	term_free_struct(&term_p);
	return (EXIT_SUCCESS);
}
