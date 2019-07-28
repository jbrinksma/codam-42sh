/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_next.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:41:00 by rkuijper       #+#    #+#                */
/*   Updated: 2019/07/15 16:34:17 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	parse_next_move_word(unsigned *index, char **line)
{
	unsigned i;

	i = *index + 1;
	if (*index == ft_strlen(*line))
		return ;
	while ((*line)[i])
	{
		if (input_is_word_start(*line, i - 1, i))
			break ;
		i++;
	}
	ft_printf("%.*s", i - *index, *line + *index);
	*index = i;
}

int			input_parse_next(t_inputdata *data, char **line)
{
	if (((data->input_state == INPUT_BRACE || data->input_state == INPUT_D_BRACE) &&
		data->c == 'C') || data->c == '\6')
	{
		if (data->input_state == INPUT_BRACE)
		{
			if (data->index < ft_strlen(*line))
			{
				ft_putchar((*line)[data->index]);
				data->index += 1;
			}
		}
		else
			parse_next_move_word(&data->index, line);
		data->input_state = INPUT_NONE;
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
