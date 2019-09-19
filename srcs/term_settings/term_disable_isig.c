/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_disable_isig.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/17 15:08:23 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/09/17 15:10:05 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <termios.h>

void		term_disable_isig(t_termios *termios_p)
{
	termios_p->c_lflag &= ~(ISIG);
	tcsetattr(STDIN_FILENO, TCSANOW, termios_p);
}
