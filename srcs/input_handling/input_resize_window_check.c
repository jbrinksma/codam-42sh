/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_resize_window_check.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/29 10:40:21 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/30 11:35:22 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <sys/ioctl.h>
#include <term.h>

static void	input_resize_window(t_vshdata *data, struct winsize new)
{
	int				newlines;
	unsigned		saved_index;
	int				extra;

	saved_index = data->line->index;
	newlines = data->curs->coords.y - 1;
	extra = 0;
	if (data->curs->cur_ws_col % new.ws_col > 0)
		extra = 1;
	if (data->curs->coords.x - 1 > 0)
		ft_printf("\e[%iD", data->curs->coords.x - 1);
	if (data->curs->cur_ws_col > new.ws_col)
		newlines *= ((data->curs->cur_ws_col / new.ws_col) + extra);
	if (newlines > 0)
		ft_printf("\e[%iA", newlines);
	tputs(data->termcaps->tc_clear_lines_str, 1, &ft_tputchar);
	data->curs->coords = (t_point){1, 1};
	data->curs->cur_ws_col = new.ws_col;
	shell_display_prompt(data, data->prompt->cur_prompt_type);
	data->line->index = data->line->len_cur;
	input_print_str(data, data->line->line);
	data->line->index = data->line->len_cur;
	curs_go_home(data);
	curs_move_n_right(data, saved_index);
}

int			input_resize_window_check(t_vshdata *data)
{
	struct winsize	new;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &new) == -1)
	{
		ft_eprintf(E_BAD_FD, STDIN_FILENO);
		builtin_exit(NULL, data);
	}
	data->curs->cur_ws_row = new.ws_row;
	if (data->curs->cur_ws_col == UNINIT)
		data->curs->cur_ws_col = new.ws_col;
	else if (data->curs->cur_ws_col != new.ws_col)
		input_resize_window(data, new);
	else
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
