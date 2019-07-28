/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_change_line.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/02 14:28:54 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/28 17:08:31 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include "libft.h"

static void	history_clear_line(unsigned *index, unsigned linelen)
{
	if (*index > 0)
		ft_printf("\e[%dD", *index);
	*index = 0;
	while (*index < linelen)
	{
		ft_putchar(' ');
		(*index)++;
	}
	if (*index > 0)
		ft_printf("\e[%dD", *index);
}

static int	malloc_and_copy(t_inputdata *data, char **line, char *str)
{
	int len;

	len = ft_strlen(str);
	if (len < data->len_max)
	{
		ft_bzero(*line, data->len_max);
	}
	else
	{
		data->len_max *= 2;
		ft_strdel(&(*line));
		*line = ft_strnew(data->len_max);
		if (*line == NULL)
			return (FUNCT_ERROR);
	}
	ft_strcpy(*line, str);
	return (FUNCT_SUCCESS);
}

static int	set_line(t_inputdata *data, char **line, int change)
{
	data->hist_index += change;
	if (malloc_and_copy(data, line, data->history[data->hist_index]->str)
	== FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}

int			history_change_line(t_inputdata *data, char **line, char arrow)
{
	history_clear_line(&(data->index), ft_strlen(*line));
	if (arrow == ARROW_UP && (data->hist_index - 1) >= 0 &&
	data->history[(data->hist_index - 1)]->str != NULL)
	{
		if (set_line(data, line, -1) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	else if (arrow == ARROW_DOWN && (data->hist_index + 1) <= HISTORY_MAX &&
		data->history[(data->hist_index + 1)]->str != NULL)
	{
		if (set_line(data, line, 1) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	else if (arrow == ARROW_DOWN)
	{
		if (data->history[(data->hist_index)]->str != NULL)
			data->hist_index += 1;
		ft_bzero(*line, data->len_max);
	}
	else
		ft_printf("\a");
	ft_putstr(*line);
	data->index = ft_strlen(*line);
	return (FUNCT_SUCCESS);
}
