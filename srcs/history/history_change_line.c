/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_change_line.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/02 14:28:54 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/26 15:40:11 by jbrinksm      ########   odam.nl         */
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
	if (malloc_and_copy(data, line, data->history->current->str) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

static int	handle_arrow_keys(t_vshdata *data, char arrow)
{
	int ret;

	ret = FUNCT_FAILURE;
	if (arrow == ARROW_UP)
	{
		if (history_index_change_up(data->history) == FUNCT_SUCCESS)
			ret = set_line(data, &data->line->line);
		else
			ft_printf("\a");
	}
	else if (arrow == ARROW_DOWN)
	{
		if (history_index_change_down(data->history) == FUNCT_SUCCESS)
			ret = set_line(data, &data->line->line);
		else
			ft_bzero(data->line->line, data->line->len_max);
	}
	return (ret);
}

int			history_change_line(t_vshdata *data,
		char arrow)
{
	size_t	linelen;

	history_clear_line(data);
	if (handle_arrow_keys(data, arrow) == FUNCT_ERROR)
	{
		ft_eprintf(E_N_ALLOC_STR, "history");
		return (FUNCT_ERROR);
	}
	input_print_str(data, data->line->line);
	linelen = ft_strlen(data->line->line);
	data->line->index = linelen;
	data->line->len_cur = linelen;
	return (FUNCT_SUCCESS);
}
