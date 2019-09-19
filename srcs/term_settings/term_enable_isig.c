/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_enable_isig.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/17 15:08:20 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/09/17 15:09:36 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <termios.h>

void		term_enable_isig(t_termios *termios_p)
{
	termios_p->c_lflag |= (ISIG);
	tcsetattr(STDIN_FILENO, TCSANOW, termios_p);
}
