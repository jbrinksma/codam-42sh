/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_down.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/17 11:50:51 by rkuijper       #+#    #+#                */
/*   Updated: 2019/07/28 17:08:00 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <sys/ioctl.h>
#include <unistd.h>

static void	parse_ctrl_line_down(unsigned *index, char **line)
{
	struct winsize	ws;
	unsigned		len;

	len = ft_strlen(*line);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	if (*index + ws.ws_col < len)
	{
		ft_printf("\e[B");
		*index += ws.ws_col;
	}
	else
	{
		ft_printf("%s", *line + *index);
		*index = len;
	}
}

int			input_parse_ctrl_down(t_inputdata *data, char **line)
{
	if ((data->input_state == INPUT_BRACE
	|| data->input_state == INPUT_D_BRACE) && data->c == 'B')
	{
		if (data->input_state == INPUT_BRACE)
		{
			if (history_change_line(data, line, ARROW_DOWN) == FUNCT_ERROR)
				return (FUNCT_ERROR);
		}
		else
			parse_ctrl_line_down(&data->index, line);
		data->input_state = INPUT_NONE;
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
