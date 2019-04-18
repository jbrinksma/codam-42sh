/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_get_attributes.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 18:08:42 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/18 18:11:54 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		term_get_attributes(t_term *term_p)
{
	int	ret;

	/* Insert: check if it is a valid terminal file_d */
	ret = tcgetattr(STDIN_FILENO, term_p->termios_p);
	if (ret == FUNCT_ERROR)
	{
		ft_eprintf("Couldn't get terminal attributes.\n");
		return (FUNCT_FAILURE);
	}
	ret = tcgetattr(STDIN_FILENO, term_p->old_termios_p);
	if (ret == FUNCT_ERROR)
	{
		ft_eprintf("Couldn't get terminal attributes.\n");
		return (FUNCT_FAILURE);
	}
	return (FUNCT_SUCCESS);
}
