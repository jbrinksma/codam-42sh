/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_delete.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:44:53 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/05 17:44:00 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <term.h>

/*
**	If the cursor is anywhere but the end of the line, it will remove the
**	current character in `data->line->line` where the cursor (and thus
**	`data->line->index`) is pointing to.
**	Afterwards, it will save the current cursor position, clear the whole line,
**	reprint the new line without the removed char, and then reset the cursor to
**	the old position.
*/

void		input_handle_delete(t_vshdata *data)
{
	unsigned	saved_index;
	t_point		saved_coord;

	if (data->line->index < data->line->len_cur)
	{
		ft_memcpy(&saved_coord, &data->curs->coords, sizeof(t_point));
		input_clear_char_at(&data->line->line, data->line->index);
		ft_putstr("\e[s");
		saved_index = data->line->index;
		curs_go_home(data);
		tputs(data->termcaps->tc_clear_lines_str, 1, &ft_tputchar);
		input_print_str(data, data->line->line);
		ft_putstr("\e[u");
		data->line->index = saved_index;
		data->line->len_cur--;
		ft_memcpy(&data->curs->coords, &saved_coord, sizeof(t_point));
	}
}
