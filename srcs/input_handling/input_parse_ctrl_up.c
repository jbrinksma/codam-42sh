/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_up.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 15:03:17 by rkuijper       #+#    #+#                */
/*   Updated: 2019/08/30 16:57:27 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Moves the cursor (and index) up or sets it at home if it would otherwise
**	collide with the prompt.
*/

static unsigned	get_line_index_from(t_vshdata *data, int index)
{
	int i;

	i = index - 1;
	while (i > 0)
	{
		if (data->line->line[i] == '\n')
			return (index - i - 1);
		i--;
	}
	return (index);
}

static void		move_up_handle_newline(t_vshdata *data)
{
	unsigned	i;
	int			j;
	unsigned	l;

	i = data->line->index - 1;
	j = -1;
	l = get_line_index_from(data, data->line->index);
	while (i > 0)
	{
		if (data->line->line[i] == '\n')
		{
			if (j == -1)
				j = get_line_index_from(data, i);
			else
				break ;
		}
		else if (j != -1)
		{
			if (j <= (int)l)
				break ;
			j--;
		}
		i--;
	}
	curs_move_n_left(data, data->line->index - i - 1);
}

void			curs_move_up(t_vshdata *data)
{
	char			*newline_str;

	if (data->line->index == 0)
		return ;
	newline_str = ft_strrnchr(data->line->line, '\n', data->line->index - 1);
	if (newline_str != NULL)
		move_up_handle_newline(data);
	else if (data->line->index < (unsigned)data->curs->cur_ws_col)
		curs_go_home(data);
	else
	{
		ft_printf(CURS_UP);
		data->line->index -= data->curs->cur_ws_col;
		data->curs->coords.y--;
		data->curs->cur_relative_y--;
	}
}
