/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_init_struct.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 18:04:22 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/13 15:02:21 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <termios.h>

/*
**	Allocates a t_term* and the two termios* which it contains, and returns
**	the t_term*
**
**	*old_termios_p: will be used to save initial termios attributes
**	*termios_p: will be used to set net termios attributes
**
**	If any alloc error occurs, the succesfully allocated pointers are freed,
**	and a NULL pointer is returned.
*/

t_term	*term_init_struct(void)
{
	t_term	*term_p;

	term_p = (t_term*)ft_memalloc(sizeof(t_term));
	if (term_p == NULL)
		return (NULL);
	term_p->old_termios_p = \
	(t_termios*)ft_memalloc(sizeof(t_termios));
	if (term_p->old_termios_p == NULL)
	{
		free(term_p);
		return (NULL);
	}
	term_p->termios_p = (t_termios*)ft_memalloc(sizeof(t_termios));
	if (term_p->termios_p == NULL)
	{
		free(term_p->old_termios_p);
		free(term_p);
		return (NULL);
	}
	return (term_p);
}
