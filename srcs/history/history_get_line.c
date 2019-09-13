/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_get_line.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/10 18:35:45 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/12 18:58:49 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	History_get_index figures out at which index we need to look for a str
**	It verifies if it is within the valid range of min and max history nums
**	It sets his_index to a valid index in history or it returns failure
*/

int			history_get_index(int *his_index, int his_total, int i)
{
	if (i < 0)
		i = his_total + 1 + i;
	if (i <= 0)
		return (FUNCT_FAILURE);
	if (i > his_total || i <= his_total - HISTORY_MAX)
		return (FUNCT_FAILURE);
	*his_index = (i - 1) % HISTORY_MAX;
	return (FUNCT_SUCCESS);
}

static char	*history_get_line_at_index(t_datahistory *history, int i)
{
	int		his_index;

	his_index = 0;
	if (history_get_index(&his_index,
		history->history[history->hist_start]->number, i) == FUNCT_FAILURE)
		return (NULL);
	if (history->history[his_index] == NULL)
		return (NULL);
	return (history->history[his_index]->str);
}

char		*history_get_line(t_datahistory *history, char *line, size_t i)
{
	char	*hist_line;
	size_t	num_len;

	if (ft_isdigit(line[i + 1]) || (line[i + 1] == '-' &&
		ft_isdigit(line[i + 2])))
		hist_line = history_get_line_at_index(history, ft_atoi(&line[i + 1]));
	else if (line[i + 1] == '!')
		hist_line = history_get_line_at_index(history, -1);
	else
		return (history_match_line(history, line, i));
	if (hist_line == NULL)
	{
		num_len = history_get_match_len(line, i);
		ft_eprintf(E_HIST_NUM_ERROR, num_len + 1, &line[i]);
	}
	return (hist_line);
}
