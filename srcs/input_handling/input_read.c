/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_read.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 14:03:16 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/25 13:38:40 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>

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

int		input_read(char **line, int *status)
{
	char		c;
	unsigned	index;
	int			local_status;
	int			input_state;
	int			len_max;

	index = 0;
	input_state = 0;
	len_max = 64;
	*line = ft_strnew(len_max);
	if (*line == NULL)
		return (FUNCT_ERROR);
	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		local_status = 0;
		local_status |= input_parse_escape(c, &input_state);
		local_status |= input_parse_home(c, &input_state, &index);
		local_status |= input_parse_end(c, &input_state, &index, line);
		local_status |= input_parse_prev(c, &input_state, &index, line);
		local_status |= input_parse_next(c, &input_state, &index, line);
		local_status |= input_parse_delete(c, &input_state, &index, line);
		local_status |= input_parse_ctrl_up(c, &input_state, &index, line);
		local_status |= input_parse_ctrl_down(c, &input_state, &index, line);
		if (local_status == 0)
			input_state = 0;
		local_status |= input_parse_backspace(c, &index, line);
		local_status |= input_parse_ctrl_d(c, &index, line);
		local_status |= input_parse_ctrl_k(c, &index, line);
		if (local_status == 0 && input_parse_char(c, &index, line, &len_max) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		if (c == '\n')
			break ;
	}
	*status = local_status;
	return (FUNCT_SUCCESS);
}
