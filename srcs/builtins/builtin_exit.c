/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 20:15:24 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/18 19:15:46 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	builtin_exit(t_term *term_p)
{
	ft_putchar('\n');
	term_free_struct(term_p);
	exit(FUNCT_SUCCESS);
}
