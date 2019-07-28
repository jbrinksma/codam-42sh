/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_char.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:33:54 by rkuijper       #+#    #+#                */
/*   Updated: 2019/07/28 18:43:03 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	This function makes sure that when you are inserting a char
**	inbetween other chars on the line, that the chars on the right
**	side are moved over by 1, which creates a gap for the char
**	that needs to be inserted.
*/

static void	create_char_gap(char *line, int len, int gap_index)
{
	int	i;

	i = len;
	i--;
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

static int	add_char_at(char **line, int index, char c, int *len_max)
{
	char		*tmp;
	int			len;

	len = ft_strlen(*line);
	if (len < *len_max)
	{
		create_char_gap(*line, len, index);
		(*line)[index] = c;
	}
	else
	{
		*len_max *= 2;
		tmp = ft_strnew(*len_max);
		if (tmp == NULL)
			return (FUNCT_ERROR);
		ft_strcpy(tmp, *line);
		ft_strdel(line);
		create_char_gap(tmp, len, index);
		tmp[index] = c;
		*line = tmp;
	}
	return (FUNCT_SUCCESS);
}

/*
**	Makes sure that when a `\n` char is caught, it is put
**	at the end of `*line`. When there is not enough space
**	on line, the amount of memory for `*line` is increased
**	by 1 byte first.
*/

static int	add_newline(char **line, int *len_max)
{
	char		*tmp;
	int			len;

	len = ft_strlen(*line);
	if (len < *len_max)
		(*line)[len] = '\n';
	else
	{
		*len_max += 1;
		tmp = ft_strnew(*len_max);
		if (tmp == NULL)
			return (FUNCT_ERROR);
		ft_strcpy(tmp, *line);
		ft_strdel(line);
		tmp[len] = '\n';
		*line = tmp;
	}
	return (FUNCT_SUCCESS);
}

int			input_parse_char(t_inputdata *data, char **line)
{
	unsigned len;

	if (ft_isprint(data->c))
	{
		if (add_char_at(line, data->index, data->c, &(data->len_max))
		== FUNCT_ERROR)
			return (FUNCT_ERROR);
		len = ft_strlen(*line + data->index);
		ft_printf("%s", *line + data->index);
		if (len - 1 > 0)
			ft_printf("\e[%dD", len - 1);
		data->index += 1;
	}
	else if (data->c == '\n')
	{
		if (add_newline(line, &(data->len_max)) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	return (FUNCT_SUCCESS);
}
