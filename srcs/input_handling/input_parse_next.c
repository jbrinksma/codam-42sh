/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_next.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:41:00 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/05 17:35:58 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Small algorithm that moves the cursor (and index) to the beginning of the
**	next word (or end of the line if there is none).
*/

void		curs_move_next_word(t_vshdata *data)
{
	size_t	i;

	if (data->line->index == data->line->len_cur)
		return ;
	i = 0;
	while (tools_isprintnotblank(data->line->line[data->line->index + i])
		== true)
		i++;
	while (ft_isblank(data->line->line[data->line->index + i]) == true)
		i++;
	if ((data->line->index + i == data->line->len_cur)
		|| (tools_isprintnotblank(data->line->line[data->line->index + i]) 
		== true))
		curs_move_n_right(data, i);
}

/*
**	Calculates the column and row position that the cursor will move to
**	when it is told to move `n` times to the right. It will also increment the
**	internal index of the command line by n.
**
**	However, if a part of the line that will be traversed contains any
**	newlines, special measures wil be taken by calling a function
**	that is slower, but will accurately move the cursor when traversing
**	newlines.
*/

void		curs_move_n_right(t_vshdata *data, size_t n)
{
	int		down;
	int		x_offset;

	if (n <= 0 || data->line->index == data->line->len_cur)
		return ;
	if (n > data->line->len_cur - data->line->index)
		n = data->line->len_cur - data->line->index;
	if (ft_strchr(data->line->line, '\n') == NULL)
	{
		down = ((data->curs->coords.x - 1) + n) / data->curs->cur_ws_col;
		x_offset = (((data->curs->coords.x - 1) + n) % data->curs->cur_ws_col)
			- (data->curs->coords.x - 1);
		if (down > 0)
			ft_printf("\e[%iB", down);
		if (x_offset > 0)
			ft_printf("\e[%iC", x_offset);
		else if (x_offset < 0)
			ft_printf("\e[%iD", x_offset * -1);
		data->line->index += n;
		data->curs->coords.y += down;
		data->curs->cur_relative_y += down;
		data->curs->coords.x += x_offset;
	}
	else
		curs_move_n_right_hasnewlines(data, n);
	#ifdef DEBUG
	ft_eprintf("New cursor coordinates: [%d:%d]\n", data->curs->coords.x, data->curs->coords.y);
	#endif
}

void		curs_move_right(t_vshdata *data)
{
	curs_move_n_right(data, 1);
}
