/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_read.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 14:03:16 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/01 14:59:52 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>

void		input_clear_char_at(char **line, unsigned index)
{
	unsigned i;

	i = index;
	while ((*line)[i])
	{
		(*line)[i] = (*line)[i + 1];
		i++;
	}
}

static int	find_start(t_history **history)
{
	int i;
	int largest;
	int start;

	i = 0;
	start = 0;
	largest = -1;
	while (i < HISTORY_MAX && history[i]->str != NULL)
	{
		if (history[i]->number > largest)
		{
			start = i;
			largest = history[i]->number;
		}
		i++;
	}
	return (start + 1);
}

t_inputdata	*init_inputdata(t_vshdata *vshdata)
{
	t_inputdata	*new;

	new = (t_inputdata*)ft_memalloc(sizeof(t_inputdata));
	if (new == NULL)
		return (NULL);
	new->c = 0;
	new->index = 0;
	new->input_state = 0;
	new->hist_index = find_start(vshdata->history);
	new->hist_start = new->hist_index - 1;
	new->hist_first = true;
	new->history = vshdata->history;
	new->len_max = 64;
	return (new);
}

int			input_read(t_vshdata *vshdata, char **line, int *status)
{
	t_inputdata	*data;
	int			local_status;

	data = init_inputdata(vshdata);
	if (data == NULL)
		return (FUNCT_ERROR);
	*line = ft_strnew(data->len_max);
	if (*line == NULL)
		return (ft_free_return(data, FUNCT_ERROR));
	while (read(STDIN_FILENO, &data->c, 1) > 0)
	{
		local_status = 0;
		local_status |= input_parse_escape(data);
		local_status |= input_parse_home(data);
		local_status |= input_parse_end(data, line);
		local_status |= input_parse_prev(data, line);
		local_status |= input_parse_next(data, line);
		local_status |= input_parse_delete(data, line);
		local_status |= input_parse_ctrl_up(data, line);
		local_status |= input_parse_ctrl_down(data, line);
		if (local_status == 0)
			data->input_state = 0;
		local_status |= input_parse_backspace(data, line);
		if (input_parse_ctrl_c(data) == FUNCT_SUCCESS)
			return (ft_free_return(data, NEW_PROMPT));
		local_status |= input_parse_ctrl_d(data, vshdata, line);
		local_status |= input_parse_ctrl_k(data, line);
		if (local_status == 0 && input_parse_char(data, line) == FUNCT_ERROR)
			return (ft_free_return(data, FUNCT_ERROR));
		if (data->c == '\n')
			break ;
	}
	*status = local_status;
	return (ft_free_return(data, FUNCT_SUCCESS));
}
