/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_free_struct.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 18:18:53 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/23 14:39:13 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	term_free_struct(t_term **term_p)
{
	if (term_p != NULL && *term_p != NULL)
	{
		if ((*term_p)->old_termios_p)
			free((*term_p)->old_termios_p);
		if ((*term_p)->termios_p)
			free((*term_p)->termios_p);
		free(*term_p);
		*term_p = NULL;
	}
}
