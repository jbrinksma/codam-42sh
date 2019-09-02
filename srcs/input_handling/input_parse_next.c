/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_next.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:41:00 by rkuijper       #+#    #+#                */
/*   Updated: 2019/08/30 16:55:26 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Algorithm that moves the cursor (and index) to the beginning of the next
**	word (or end of the line if there is none).
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
**	Calculates the end position once if there are no newlines in the part
**	of the string the cursor will traverse. If there is a newline, it will
**	call a function with a slower method to reposition the cursor.
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
		data->curs->coords.x += x_offset;
	}
	else
		curs_move_n_right_hasnewlines(data, n);
	#ifdef DEBUG
	ft_eprintf("New cursor coordinates: [%d:%d]\n", data->curs->coords.x, data->curs->coords.y);
	#endif
}

/*
**	Moves the cursor (and index) one to the right (or down if necessary)
**	If used after some weird screen clearing, make sure to compensate
**	for the automatic `index` change if necessary.
*/

void		curs_move_right(t_vshdata *data)
{
	curs_move_n_right(data, 1);
}
