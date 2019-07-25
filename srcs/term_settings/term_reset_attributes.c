/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_reset_attributes.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 18:19:47 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/23 14:38:01 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <termios.h>
#include <unistd.h>

/*
**	We will need to implement errno return values for this function.
*/

int		term_reset(t_term *term_p)
{
	int	ret;

	ret = tcsetattr(STDIN_FILENO, TCSANOW, term_p->old_termios_p);
	if (ret == -1)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
