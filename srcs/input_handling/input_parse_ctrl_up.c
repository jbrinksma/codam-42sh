/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_up.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 15:03:17 by rkuijper       #+#    #+#                */
/*   Updated: 2019/06/02 15:13:57 by mavan-he      ########   odam.nl         */
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
		ft_printf("\e[%dD", *index);
		*index = 0;
	}
}

int			input_parse_ctrl_up(char c, int *input_state,
	unsigned *index, char **line)
{
	(void)line;
	if ((*input_state == INPUT_BRACE || *input_state == INPUT_D_BRACE) &&
		c == 'A')
	{
		if (*input_state == INPUT_BRACE)
			history_change_line(line, index, ARROW_UP);
		else
			parse_ctrl_line_up(index);
		*input_state = INPUT_NONE;
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
