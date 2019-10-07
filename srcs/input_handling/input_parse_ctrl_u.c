/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_ctrl_u.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/23 12:15:47 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/06 10:09:01 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <term.h>

/*
**	Cuts the whole left side of the cursor (excluding the cursor itself) and
**	copies it into internal memory for potential insertion through CTRL+Y.
*/

void		input_parse_ctrl_u(t_vshdata *data)
{
	if (data->line->index > 0)
	{
		if (data->line->line_copy != NULL)
			ft_strdel(&data->line->line_copy);
		data->line->line_copy = ft_strndup(data->line->line, data->line->index);
		ft_memcpy(data->line->line, &data->line->line[data->line->index],
			data->line->index);
		ft_bzero(&data->line->line[data->line->index],
			data->line->len_cur - data->line->index);
		curs_go_home(data);
		tputs(data->termcaps->tc_clear_lines_str, 1, &ft_tputchar);
		data->line->len_cur = ft_strlen(data->line->line);
		data->line->index = data->line->len_cur;
		input_print_str(data, data->line->line);
		curs_go_home(data);
	}
}
