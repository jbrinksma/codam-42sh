/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   curs_move_n_left_hasnewlines.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/30 11:34:28 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/09/03 17:36:22 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	move_left_parse_newline(t_vshdata *data)
{
	char	*pos;
	int		len;

	pos = ft_strrnchr(data->line->line, '\n', data->line->index);
	len = data->line->index;
	if (pos != NULL)
		len = data->line->index - (pos - data->line->line);
	else
		len = (data->line->index + data->prompt->prompt_len + 1) %
			data->curs->cur_ws_col;
	ft_putstr("\e[A");
	if (len > 1)
		ft_printf("\e[%iC", len - 1);
	data->curs->coords.x = len;
	data->curs->coords.y--;
	data->curs->cur_relative_y--;
}

static void	move_left_to_colmax(t_vshdata *data, int colmax, size_t *n)
{
	int	amt;

	if (data->curs->coords.x == 1)
	{
		data->curs->coords.x = colmax;
		data->curs->coords.y--;
		data->curs->cur_relative_y--;
		ft_printf("\e[A\e[%iC", data->curs->coords.x);
		data->line->index--;
		(*n)--;
	}
	else
	{
		if (*n >= (size_t)data->curs->coords.x)
			amt = data->curs->coords.x - 1;
		else
			amt = *n;
		ft_printf("\e[%dD", amt);
		data->curs->coords.x = data->curs->coords.x - amt;
		*n -= amt;
		data->line->index -= amt;
	}
}

void		curs_move_n_left_hasnewlines(t_vshdata *data, size_t n)
{
	while (n > 0)
	{
		if (data->line->line[data->line->index - 1] == '\n')
		{
			n--;
			data->line->index--;
			move_left_parse_newline(data);
		}
		else
			move_left_to_colmax(data, data->curs->cur_ws_col, &n);
	}
}
