/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_set_attributes.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 18:11:05 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/09/17 16:52:45 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <termios.h>
#include <unistd.h>

int		term_set_attributes(t_vshdataterm *term_p)
{
	int	ret;

	term_p->termios_p->c_lflag &= ~(ECHO | ICANON);
	term_p->termios_p->c_cc[VMIN] = 1;
	term_p->termios_p->c_cc[VTIME] = 0;
	ret = tcsetattr(STDIN_FILENO, TCSANOW, term_p->termios_p);
	if (ret == -1)
	{
		ft_eprintf(E_TERM_CNT_GET);
		return (FUNCT_FAILURE);
	}
	return (FUNCT_SUCCESS);
}
