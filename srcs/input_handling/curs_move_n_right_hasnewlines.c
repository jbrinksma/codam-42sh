/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   curs_move_n_right_hasnewlines.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/30 11:32:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/26 12:50:29 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	move_right_parse_newline(t_vshdata *data)
{
	char	*pos;
	int		len;

	pos = ft_strrnchr(data->line->line, '\n', data->line->index);
	len = data->line->index + data->prompt->prompt_len;
	if (pos != NULL)
		len = data->line->index - (pos - data->line->line);
	ft_putstr("\e[B");
	if (len > 1)
		ft_printf("\e[%iD", len);
	data->curs->coords.x = 1;
	data->curs->coords.y++;
	data->curs->cur_relative_y++;
}

void		curs_move_right_at_colmax(t_vshdata *data, int colmax)
{
	if (data->curs->coords.x == colmax)
	{
		data->curs->coords.x = 1;
		data->curs->coords.y++;
		data->curs->cur_relative_y++;
		ft_printf("\e[B\e[%iD", colmax);
	}
	else
	{
		ft_putstr("\e[C");
		data->curs->coords.x++;
	}
}

void		curs_move_n_right_hasnewlines(t_vshdata *data, size_t n)
{
	while (n > 0 && data->line->line[data->line->index] != '\0')
	{
		if (data->line->line[data->line->index] == '\n'
			&& data->line->index != data->line->len_cur - 1)
			move_right_parse_newline(data);
		else
			curs_move_right_at_colmax(data, data->curs->cur_ws_col);
		n--;
		data->line->index++;
	}
}
