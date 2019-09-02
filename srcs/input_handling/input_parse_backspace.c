/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_backspace.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:43:07 by rkuijper       #+#    #+#                */
/*   Updated: 2019/08/29 11:28:22 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <term.h>

/*
**	Backspaces are handled saving the cursor position and then clearing the
**	screen and then reprinting the edited line and then going back to the old
**	cursor position.
*/

void	input_handle_backspace(t_vshdata *data)
{
	int			len_left;
	int			saved_index;

	if (data->line->index > 0)
	{
		saved_index = data->line->index;
		len_left = data->line->len_cur - data->line->index;
		data->line->len_cur--;
		curs_go_home(data);
		input_clear_char_at(&data->line->line, saved_index - 1);
		tputs(data->termcaps->tc_clear_lines_str, 1, &ft_tputchar);
		input_print_str(data, data->line->line);
		data->line->index = data->line->len_cur;
		curs_move_n_left(data, len_left);
	}
}
