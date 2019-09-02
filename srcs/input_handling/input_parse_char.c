/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_char.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:33:54 by rkuijper       #+#    #+#                */
/*   Updated: 2019/08/30 16:53:50 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <termcap.h>

/*
**	This function makes sure that when you are inserting a char
**	inbetween other chars on the line, that the chars on the right
**	side are moved over by 1, which creates a gap for the char
**	that needs to be inserted.
*/

static void	create_char_gap(char *line, int len, int gap_index)
{
	int	i;

	i = len - 1;
	while (i >= gap_index)
	{
		line[i + 1] = line[i];
		i--;
	}
}

/*
**	Inserts a char `c` at `index` on `*line`.
**	When there is not enough space on `*line`, the amount
**	of memory allocated for `*line` is doubled first.
*/

static int	add_char_at(t_vshdata *data, char **line)
{
	char	*tmp;

	if (data->line->len_cur < data->line->len_max)
	{
		create_char_gap(*line, data->line->len_cur, data->line->index);
		(*line)[data->line->index] = data->input->c;
	}
	else
	{
		while (data->line->len_cur >= data->line->len_max)
			data->line->len_max *= 2;
		tmp = ft_strnew(data->line->len_max);
		if (tmp == NULL)
			return (FUNCT_ERROR);
		ft_strcpy(tmp, *line);
		ft_strdel(line);
		create_char_gap(tmp, data->line->len_cur, data->line->index);
		tmp[data->line->index] = data->input->c;
		*line = tmp;
	}
	data->line->len_cur++;
	return (FUNCT_SUCCESS);
}

/*
**	Makes sure that when a `\n` char is caught, it is put
**	at the end of `*line`. When there is not enough space
**	on line, the amount of memory for `*line` is increased
**	by 1 byte first.
*/

static int	add_newline(t_vshdata *data, char **line)
{
	char	*tmp;

	if (data->line->len_cur < data->line->len_max)
		(*line)[data->line->len_cur] = '\n';
	else
	{
		data->line->len_max += 1;
		tmp = ft_strnew(data->line->len_max);
		if (tmp == NULL)
			return (FUNCT_ERROR);
		ft_strcpy(tmp, *line);
		ft_strdel(line);
		tmp[data->line->len_cur] = '\n';
		*line = tmp;
	}
	data->line->len_cur++;
	return (FUNCT_SUCCESS);
}

int			input_parse_char(t_vshdata *data)
{
	int	old_index;

	if (ft_isprint(data->input->c))
	{
		if (add_char_at(data, &data->line->line) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		old_index = data->line->index;
		input_print_str(data, data->line->line + data->line->index);
		data->line->index = data->line->len_cur;
		curs_move_n_left(data, data->line->index - old_index - 1);
	}
	else if (data->input->c == '\n')
	{
		if (add_newline(data, &data->line->line) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	return (FUNCT_SUCCESS);
}
