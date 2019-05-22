/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_read.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 14:03:16 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/22 11:57:34 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	input_clear_char_at(char **line, unsigned index)
{
	unsigned i;

	i = index;
	while ((*line)[i])
	{
		(*line)[i] = (*line)[i + 1];
		i++;
	}
}

int		input_read(char **line)
{
	char		c;
	unsigned	index;
	int			status;
	int			input_state;

	index = 0;
	input_state = 0;
	*line = ft_strnew(0);
	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		if (c == '\n')
			break ;
		status = 0;
		status |= input_parse_escape(c, &input_state);
		status |= input_parse_home(c, &input_state, &index);
		status |= input_parse_end(c, &input_state, &index, line);
		status |= input_parse_prev(c, &input_state, &index, line);
		status |= input_parse_next(c, &input_state, &index, line);
		status |= input_parse_delete(c, &input_state, &index, line);
		status |= input_parse_ctrl_up(c, &input_state, &index, line);
		status |= input_parse_ctrl_down(c, &input_state, &index, line);
		if (status == 0)
			input_state = 0;
		status |= input_parse_backspace(c, &index, line);
		status |= input_parse_ctrl_d(c, &index, line);
		status |= input_parse_ctrl_k(c, &index, line);
		if (status == 0 &&
			input_parse_char(c, &index, line) == FUNCT_FAILURE)
			return (FUNCT_FAILURE);
	}
	return (status);
}
