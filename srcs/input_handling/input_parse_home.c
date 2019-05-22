/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_home.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:37:33 by rkuijper       #+#    #+#                */
/*   Updated: 2019/05/22 11:57:00 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int	input_parse_home(char c, int *input_state, unsigned *index)
{
	if ((*input_state == INPUT_BRACE && c == 'H') || c == '\1')
	{
		ft_printf("\e[%dD", *index);
		*index = 0;
		*input_state = INPUT_NONE;
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
