/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_up.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 15:03:17 by rkuijper       #+#    #+#                */
/*   Updated: 2019/07/31 13:30:15 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <sys/ioctl.h>
#include <unistd.h>

static void	parse_ctrl_line_up(unsigned *index)
{
	struct winsize	ws;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	if (*index >= ws.ws_col)
	{
		ft_printf("\e[A");
		*index -= ws.ws_col;
	}
	else
	{
		if (*index > 0)
			ft_printf("\e[%dD", *index);
		*index = 0;
	}
}

int			input_parse_ctrl_up(t_inputdata *data, char **line)
{
	(void)line;
	if (((data->input_state == INPUT_BRACE
	|| data->input_state == INPUT_D_BRACE) && data->c == 'A') ||
	(data->input_state == INPUT_ESC && data->c == 10))
	{
		if (data->input_state == INPUT_BRACE)
		{
			if (history_change_line(data, line, ARROW_UP) == FUNCT_ERROR)
				return (FUNCT_ERROR);
		}
		else
			parse_ctrl_line_up(&data->index);
		data->input_state = INPUT_NONE;
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
