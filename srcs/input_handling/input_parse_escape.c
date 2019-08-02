/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_escape.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:36:25 by rkuijper       #+#    #+#                */
/*   Updated: 2019/08/02 10:03:20 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int	input_parse_escape(t_inputdata *data)
{
	if (data->input_state == INPUT_NONE && data->c == '\e')
		data->input_state = INPUT_ESC;
	else if (data->input_state == INPUT_ESC && data->c == '\e')
		data->input_state = INPUT_D_ESC;
	else if ((data->input_state == INPUT_ESC
			|| data->input_state == INPUT_D_ESC) && data->c == '[')
		(data->input_state)++;
	else if ((data->input_state == INPUT_BRACE
			|| data->input_state == INPUT_D_BRACE) && data->c == '3')
		(data->input_state)++;
	else
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
