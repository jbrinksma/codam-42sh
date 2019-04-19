/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_reset_attributes.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 18:19:47 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/18 18:19:56 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		term_reset(t_term *term_p)
{
	int	ret;

	/* Is TCSANOW flag correct? */
	ret = tcsetattr(STDIN_FILENO, TCSANOW, term_p->old_termios_p);
	if (ret == -1)
		return (FUNCT_SUCCESS);
	return (FUNCT_SUCCESS);
}
