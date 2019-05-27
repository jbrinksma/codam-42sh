/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_reset_attributes.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 18:19:47 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/27 10:21:17 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	We will need to implement errno return values for this function.
*/

int		term_reset(t_term *term_p)
{
	int	ret;

	/* Is TCSANOW flag correct? */
	ret = tcsetattr(STDIN_FILENO, TCSANOW, term_p->old_termios_p);
	if (ret == -1)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
