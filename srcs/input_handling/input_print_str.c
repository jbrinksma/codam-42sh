/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_print_str.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/23 11:54:27 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/27 21:26:00 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vsh.h>
#include <termios.h>
#include <term.h>

/*
**	Scrolls the terminal (and the cursor) down one line.
*/

static void	scroll_down_terminal(t_vshdata *data)
{
	ft_printf("\e[%iD", data->curs->coords.x - 1);
	tputs(data->termcaps->tc_scroll_down_str, 1, &ft_tputchar);
	ft_printf("\e[%iC", data->curs->coords.x - 1);
}

static void	update_newline_coords(t_vshdata *data)
{
	data->curs->coords.x = 1;
	data->curs->cur_relative_y++;
}

/*
**	A special version of `ft_putstr` which makes sure that whenever the
**	cursor is about to walk off the right of the terminal, it is placed
**	a row down. If the cursor is already on the last row, the terminal will
**	be scrolled down one line to make room for it.
*/

void		input_print_str(t_vshdata *data, char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		data->curs->coords.x++;
		if (str[i] == '\n')
		{
			update_newline_coords(data);
			if (data->curs->coords.y < data->curs->cur_ws_row)
				data->curs->coords.y++;
		}
		if (data->curs->coords.x > data->curs->cur_ws_col)
		{
			if (data->curs->coords.y == data->curs->cur_ws_row)
				scroll_down_terminal(data);
			else
				data->curs->coords.y++;
			ft_printf("\e[B\e[%iD", data->curs->cur_ws_col);
			update_newline_coords(data);
		}
		i++;
	}
}
