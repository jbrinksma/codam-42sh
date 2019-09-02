/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_change_line.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/02 14:28:54 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/30 17:06:18 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include "libft.h"
#include <term.h>

/*
**	Cursor (and index) will be moved to the start of the string. The screen will
**	be cleared from that line and onwards. A new prompt will be displayed.
*/

static void	history_clear_line(t_vshdata *data)
{
	curs_go_home(data);
	tputs(data->termcaps->tc_clear_lines_str, 1, &ft_tputchar);
}

static int	malloc_and_copy(t_vshdata *data, char **line, char *str)
{
	unsigned	len;

	len = ft_strlen(str);
	if (len < data->line->len_max)
	{
		ft_bzero(*line, data->line->len_max);
	}
	else
	{
		while (len >= data->line->len_max)
			data->line->len_max *= 2;
		ft_strdel(&(*line));
		*line = ft_strnew(data->line->len_max);
		if (*line == NULL)
			return (FUNCT_ERROR);
	}
	ft_strcpy(*line, str);
	return (FUNCT_SUCCESS);
}

static int	set_line(t_vshdata *data, char **line)
{
	if (malloc_and_copy(data, line,
		data->history->history[data->history->hist_index]->str) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

int			history_change_line(t_vshdata *data,
		char arrow)
{
	size_t	linelen;

	history_clear_line(data);
	if (arrow == ARROW_UP)
	{
		if (history_index_change_up(data))
			set_line(data, &data->line->line);
		else
			ft_printf("\a");
	}
	else if (arrow == ARROW_DOWN)
	{
		if (history_index_change_down(data))
			set_line(data, &data->line->line);
		else
			ft_bzero(data->line->line, data->line->len_max);
	}
	input_print_str(data, data->line->line);
	linelen = ft_strlen(data->line->line);
	data->line->index = linelen;
	data->line->len_cur = linelen;
	return (FUNCT_SUCCESS);
}
