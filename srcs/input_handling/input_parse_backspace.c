/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_backspace.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:43:07 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/28 16:02:25 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <term.h>

/*
**	Backspaces are handled saving the cursor position and then clearing the
**	screen and then reprinting the edited line and then going back to the old
**	cursor position.
*/

static void	input_handle_backspace_og(t_vshdata *data)
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

/*
**  If ctrl+r is active -> clear the line, remove the char, search again
**  starting from the beginning of the history list, print the result.
**  if ctrl+r is not active the regular backspace function is called.
*/

int			input_handle_backspace(t_vshdata *data)
{
	if (data->input->searchhistory.active && data->line->index > 0)
	{
		if (ctrlr_clear_line(data) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		data->line->index = ft_strlen(data->line->line);
		input_clear_char_at(&data->line->line, ft_strlen(data->line->line) - 1);
		data->line->len_cur--;
		data->input->searchhistory.current = data->history->tail;
		if (history_ctrl_r(data, true) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		input_print_ctrl_r(data, data->line->line,
		data->input->searchhistory.result_str,
		data->input->searchhistory.result_i);
	}
	else
		input_handle_backspace_og(data);
	return (FUNCT_SUCCESS);
}
