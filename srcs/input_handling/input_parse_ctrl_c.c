/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_c.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/29 13:54:20 by tde-jong       #+#    #+#                */
/*   Updated: 2019/08/29 12:07:06 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <term.h>

/*
**	Moves past the commandline and then displays a new prompt.
*/

int		input_parse_ctrl_c(t_vshdata *data)
{
	if (data->input->c == INPUT_CTRL_C)
	{
		curs_go_end(data);
		ft_putchar('\n');
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
