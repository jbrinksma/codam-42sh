/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_down.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/17 11:50:51 by rkuijper       #+#    #+#                */
/*   Updated: 2019/05/21 12:17:15 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <sys/ioctl.h>

static void		parse_ctrl_line_down(unsigned *index, char **line)
{
	struct ttysize		ts;
	unsigned			len;

	len = ft_strlen(*line);
	ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
	if (*index + ts.ts_cols < len)
	{
		ft_printf("\e[B");
		*index += ts.ts_cols;
	}
	else
	{
		ft_printf("%s", *line + *index);
		*index = len;
	}
}

int				input_parse_ctrl_down(char c, int *input_state,
	unsigned *index, char **line)
{
	if ((*input_state == INPUT_BRACE || *input_state == INPUT_D_BRACE) &&
		c == 'B')
	{
		if (*input_state == INPUT_BRACE)
			;
		else
			parse_ctrl_line_down(index, line);
		*input_state = INPUT_NONE;
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}
