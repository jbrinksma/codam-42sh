/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_free_struct.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 18:18:53 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/19 19:19:30 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	term_free_struct(t_term **term_p)
{
	if (term_p)
	{
		if (*term_p)
		{
			if ((*term_p)->old_termios_p)
				free((*term_p)->old_termios_p);
			if ((*term_p)->termios_p)
				free((*term_p)->termios_p);
			free(*term_p);
			*term_p = NULL;
		}
	}
}
