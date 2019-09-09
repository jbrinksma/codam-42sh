/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_down.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/17 11:50:51 by rkuijper       #+#    #+#                */
/*   Updated: 2019/08/30 16:57:20 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Moves the cursor (and index) down or sets it at end if it would otherwise
**	get out of bounds.
*/

static unsigned	get_cur_line_index(t_vshdata *data)
{
	int i;

	i = data->line->index - 1;
	while (i > 0)
	{
		if (data->line->line[i] == '\n')
			return (data->line->index - i - 1);
		i--;
	}
	return (data->line->index);
}

static void		move_down_handle_newline(t_vshdata *data)
{
	unsigned	i;
	int			j;
	unsigned	l;

	i = data->line->index;
	j = -1;
	l = get_cur_line_index(data);
	while (data->line->line[i] != '\0')
	{
		if (data->line->line[i] == '\n')
		{
			if (j == -1)
				j = 0;
			else
				break ;
		}
		else if (j != -1)
		{
			if (j >= (int)l)
				break ;
			j++;
		}
		i++;
	}
	curs_move_n_right(data, i - data->line->index);
}

void			curs_move_down(t_vshdata *data)
{
	char			*newline_str;

	if (data->line->index == data->line->len_cur)
		return ;
	newline_str = ft_strchr(data->line->line + data->line->index, '\n');
	if (newline_str != NULL)
		move_down_handle_newline(data);
	else if (data->line->len_cur - data->line->index <
		(unsigned)data->curs->cur_ws_col)
		curs_go_end(data);
	else
	{
		ft_printf(CURS_DOWN);
		data->line->index += data->curs->cur_ws_col;
		data->curs->coords.y++;
		data->curs->cur_relative_y++;
	}
}
