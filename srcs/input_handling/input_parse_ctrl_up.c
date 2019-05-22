/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_up.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 15:03:17 by rkuijper       #+#    #+#                */
/*   Updated: 2019/05/21 12:16:35 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <sys/ioctl.h>

static void		parse_ctrl_line_up(unsigned *index)
{
	struct ttysize		ts;

	ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
	if (*index >= ts.ts_cols)
	{
		ft_printf("\e[A");
		*index -= ts.ts_cols;
	}
	else
	{
		ft_printf("\e[%dD", *index);
		*index = 0;
	}
}

int				input_parse_ctrl_up(char c, int *input_state,
	unsigned *index, char **line)
{
	(void)line;
	if ((*input_state == INPUT_BRACE || *input_state == INPUT_D_BRACE) &&
		c == 'A')
	{
		if (*input_state == INPUT_BRACE)
			;
		else
			parse_ctrl_line_up(index);
		*input_state = INPUT_NONE;
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
