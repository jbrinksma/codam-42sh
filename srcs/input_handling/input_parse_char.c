/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_char.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/16 13:33:54 by rkuijper       #+#    #+#                */
/*   Updated: 2019/07/13 18:40:43 by jbrinksm      ########   odam.nl         */
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
			return (FUNCT_FAILURE);
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
		*len_max += 1; // keep for clarity?
		tmp = ft_strnew(*len_max + 1);
		if (tmp == NULL)
			return (FUNCT_FAILURE);
		ft_strcpy(tmp, *line);
		ft_strdel(line);
		tmp[len] = '\n';
		*line = tmp;
	}
	return (FUNCT_SUCCESS);
}

int			input_parse_char(char c, unsigned *index, char **line, int *len_max)
{
	unsigned len;

	if (ft_isprint(c))
	{
		if (add_char_at(line, *index, c, len_max) == FUNCT_FAILURE)
			return (FUNCT_FAILURE);
		len = ft_strlen(*line + *index);
		ft_printf("%s", *line + *index);
		if (len - 1 > 0)
			ft_printf("\e[%dD", len - 1);
		*index += 1;
	}
	else if (c == '\n')
	{
		if (add_newline(line, len_max) == FUNCT_FAILURE)
			return (FUNCT_FAILURE);
	}
	return (FUNCT_SUCCESS);
}
