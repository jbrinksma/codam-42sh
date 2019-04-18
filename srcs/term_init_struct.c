/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_init_struct.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 18:04:22 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/18 18:10:08 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

t_term	*term_init_struct(void)
{
	t_term	*term_p;

	term_p = (t_term*)malloc(sizeof(t_term));
	if (!term_p)
		return (NULL);
	term_p->old_termios_p = (struct termios*)malloc(sizeof(struct termios));
	if (!term_p->old_termios_p)
	{
		free(term_p);
		return (NULL);
	}
	term_p->termios_p = (struct termios*)malloc(sizeof(struct termios));
	if (!term_p->termios_p)
	{
		free(term_p->old_termios_p);
		free(term_p);
		return (NULL);
	}
	return (term_p);
}
