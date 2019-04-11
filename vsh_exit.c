/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vsh_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 20:15:24 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/11 20:15:39 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	vsh_exit(t_term *term_p)
{
	free_term_p(term_p);
	exit(FUNCT_SUCCESS);
}
