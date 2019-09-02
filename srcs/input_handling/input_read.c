/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_read.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 14:03:16 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/09/02 13:58:55 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>

static int	find_start(t_history **history)
{
	int i;
	int start;
	int largest;

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

static int	reset_input_read_return(t_vshdata *data, int ret)
{
	data->input->c = '\0';
	data->line->index = 0;
	data->line->len_max = 64;
	data->line->len_cur = 0;
	data->curs->coords.x = data->prompt->prompt_len + 1;
	data->curs->coords.y = 1;
	data->history->hist_index = find_start(data->history->history);
	data->history->hist_start = data->history->hist_index - 1;
	data->history->hist_first = true;
	return (ret);
}

static int	input_parse(t_vshdata *data)
{
	int		ret;

	if (input_parse_ctrl_c(data) == FUNCT_SUCCESS)
		return (reset_input_read_return(data, NEW_PROMPT));
	ret = input_parse_ctrl_d(data);
	if (ret == NEW_PROMPT)
		return (reset_input_read_return(data, NEW_PROMPT));
	else if (ret == FUNCT_SUCCESS)
		return (FUNCT_SUCCESS);
	else if (input_read_ansi(data) == FUNCT_FAILURE)
	{
		if (input_parse_special(data) == FUNCT_FAILURE)
		{
			if (input_parse_char(data) == FUNCT_ERROR)
				return (reset_input_read_return(data, FUNCT_ERROR));
		}
	}
	return (FUNCT_SUCCESS);
}

int			input_read(t_vshdata *data)
{
	if (data == NULL)
		return (FUNCT_ERROR);
	data->line->line = ft_strnew(data->line->len_max);
	if (data->line->line == NULL)
		return (reset_input_read_return(data, FUNCT_ERROR));
	reset_input_read_return(data, 0);
	while (true)
	{
		if (input_resize_window_check(data) == FUNCT_ERROR)
			return (reset_input_read_return(data, FUNCT_ERROR));
		if (read(STDIN_FILENO, &data->input->c, 1) == -1)
			return (reset_input_read_return(data, FUNCT_ERROR));
		if (input_parse(data) == NEW_PROMPT)
			return (NEW_PROMPT);
		if (data->input->c == '\n')
		{
			curs_go_end(data);
			break ;
		}
		data->input->c = '\0';
	}
	return (reset_input_read_return(data, FUNCT_SUCCESS));
}
