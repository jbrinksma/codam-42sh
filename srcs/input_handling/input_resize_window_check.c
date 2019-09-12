/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_resize_window_check.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/29 10:40:21 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/09/11 18:36:25 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <term.h>
#include <signal.h>
#include <sys/ioctl.h>

static void	input_resize_window(t_vshdata *data, struct winsize new)
{
	int				newlines;
	unsigned		saved_index;
	int				extra;

	saved_index = data->line->index;
	newlines = data->curs->cur_relative_y - 1;
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

/*
**	A signal function to catch window resize events.
**	Gets called for the first time in main() to initialize
**	window size variables, for later resize purposes
**	and to bind the SIGWINCH signal event to the method.
*/

void		resize_window_check(int sig)
{
	struct winsize ws;

	if (sig == SIGWINCH)
	{
		if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
		{
			ft_eprintf(E_BAD_FD, STDIN_FILENO);
			builtin_exit(NULL, g_data);
		}
		g_data->curs->cur_ws_row = ws.ws_row;
		if (g_data->curs->cur_ws_col == UNINIT)
			g_data->curs->cur_ws_col = ws.ws_col;
		else if (g_data->curs->cur_ws_col != ws.ws_col)
			input_resize_window(g_data, ws);
	}
	signal(SIGWINCH, resize_window_check);
}
