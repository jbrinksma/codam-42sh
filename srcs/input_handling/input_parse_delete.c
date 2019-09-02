/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_delete.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:44:53 by rkuijper       #+#    #+#                */
/*   Updated: 2019/08/29 12:04:14 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <term.h>

/*
**	Real line gets updated, then the cursor position is saved
**	Lines will be cleared and everything will be reprinted
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
