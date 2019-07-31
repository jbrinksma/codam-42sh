/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_prev.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:39:59 by rkuijper       #+#    #+#                */
/*   Updated: 2019/07/31 13:27:13 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	parse_prev_move_word(unsigned *index, char **line)
{
	unsigned i;

	i = *index;
	if (*index == 0)
		return ;
	while (i > 0)
	{
		if (input_is_word_start(*line, i - 1, i) && i != *index)
			break ;
		i--;
	}
	ft_printf("\e[%dD", *index - i);
	*index = i;
}

int			input_parse_prev(t_inputdata *data, char **line)
{
	if (((data->input_state == INPUT_BRACE ||
	data->input_state == INPUT_D_BRACE) && data->c == 'D') ||
	(data->input_state == INPUT_ESC && data->c == 'b'))
	{
		if (data->input_state == 2)
		{
			if (data->index > 0)
			{
				ft_printf("\e[D");
				data->index -= 1;
			}
		}
		else
			parse_prev_move_word(&data->index, line);
		data->input_state = INPUT_NONE;
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
