/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_backspace.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:43:07 by rkuijper       #+#    #+#                */
/*   Updated: 2019/07/15 16:32:09 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		input_parse_backspace(t_inputdata *data, char **line)
{
	unsigned len;

	if (data->c == INPUT_BACKSPACE)
	{
		if (data->index > 0)
		{
			input_clear_char_at(line, data->index - 1);
			ft_printf("\e[D%s \e[D", *line + data->index - 1);
			len = ft_strlen(&(*line)[data->index - 1]);
			if (len > 1)
				ft_printf("\e[%dD", len);
			(data->index)--;
		}
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
