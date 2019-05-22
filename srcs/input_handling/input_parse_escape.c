/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_escape.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:36:25 by rkuijper       #+#    #+#                */
/*   Updated: 2019/05/21 12:17:34 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int				input_parse_escape(char c, int *input_state)
{
	if (*input_state == INPUT_NONE && c == '\e')
		*input_state = INPUT_ESC;
	else if (*input_state == INPUT_ESC && c == '\e')
		*input_state = INPUT_D_ESC;
	else if ((*input_state == INPUT_ESC || *input_state == INPUT_D_ESC)
			&& c == '[')
		(*input_state)++;
	else if ((*input_state == INPUT_BRACE || *input_state == INPUT_D_BRACE)
			&& c == '3')
		(*input_state)++;
	else
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
