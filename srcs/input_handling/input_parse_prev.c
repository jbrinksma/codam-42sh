/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_prev.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:39:59 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/05 17:35:39 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Small algorithm that moves the cursor (and index) to the beginning of a
**	previous word (or beginning of the line if there is none).
*/

void		curs_move_prev_word(t_vshdata *data)
{
	int	i;

	if (data->line->index == 0)
		return ;
	i = 0;
	if ((data->line->index > 0
		&& tools_isprintnotblank(data->line->line[data->line->index]) == true
		&& ft_isblank(data->line->line[data->line->index - 1]) == true)
		|| (data->line->index > 0 && data->line->index == data->line->len_cur))
		i++;
	while (data->line->index - i > 0
		&& ft_isblank(data->line->line[data->line->index - i]) == true)
		i++;
	if (data->line->index - i == 0)
		curs_move_n_left(data, i);
	else
	{
		while (data->line->index - i > 0 && tools_isprintnotblank(
				data->line->line[data->line->index - i - 1]))
			i++;
		curs_move_n_left(data, i);
	}
}

/*
**	Calculates the column and row position that the cursor will move to
**	when it is told to move `n` times to the left. It will also decrement the
**	internal index of the command line by n.
**
**	However, if a part of the line that will be traversed contains any
**	newlines, special measures wil be taken by calling a function
**	that is slower, but will accurately move the cursor when traversing
**	newlines.
*/

void		curs_move_n_left(t_vshdata *data, size_t n)
{
	int		up;
	int		x_offset;
	int		curs_row_pos;

	if (n <= 0 || data->line->index == 0)
		return ;
	if (n > data->line->index)
		n = data->line->index;
	if (ft_strchr(data->line->line, '\n') == NULL)
	{
		curs_row_pos = data->curs->cur_ws_col - data->curs->coords.x;
		up = (curs_row_pos + n) / data->curs->cur_ws_col;
		x_offset = curs_row_pos - ((curs_row_pos + n) % data->curs->cur_ws_col);
		if (up > 0)
			ft_printf("\e[%iA", up);
		if (x_offset > 0)
			ft_printf("\e[%iC", x_offset);
		else if (x_offset < 0)
			ft_printf("\e[%iD", x_offset * -1);
		data->line->index -= n;
		data->curs->coords.y -= up;
		data->curs->cur_relative_y -= up;
		data->curs->coords.x += x_offset;
	}
	else
		curs_move_n_left_hasnewlines(data, n);
	#ifdef DEBUG
	ft_eprintf("New cursor coordinates: [%d:%d]\n", data->curs->coords.x, data->curs->coords.y);
	#endif
}

void		curs_move_left(t_vshdata *data)
{
	curs_move_n_left(data, 1);
}
