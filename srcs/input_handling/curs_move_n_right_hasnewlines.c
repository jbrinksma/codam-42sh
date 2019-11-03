/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   curs_move_n_right_hasnewlines.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/30 11:32:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/11/01 13:44:24 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	move_right_parse_newline(t_vshdata *data)
{
	ft_putstr("\e[1E");
	data->curs->coords.x = 1;
	data->curs->coords.y++;
	data->curs->cur_relative_y++;
}

void		curs_move_right_check_colmax(t_vshdata *data, int colmax)
{
	data->curs->coords.x++;
	if (data->curs->coords.x > colmax)
	{
		data->curs->coords.x = 1;
		data->curs->coords.y++;
		data->curs->cur_relative_y++;
		ft_printf("\e[1E", colmax);
	}
	else
		ft_putstr("\e[1C");
}

void		curs_move_n_right_hasnewlines(t_vshdata *data, size_t n)
{
	while (n > 0 && data->line->line[data->line->index] != '\0')
	{
		if (data->line->line[data->line->index] == '\n'
			&& data->line->index != data->line->len_cur - 1)
			move_right_parse_newline(data);
		else
			curs_move_right_check_colmax(data, data->curs->cur_ws_col);
		n--;
		data->line->index++;
	}
}
