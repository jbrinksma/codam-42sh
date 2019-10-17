/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_get_line.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/10 18:35:45 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/15 14:59:49 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	History_get_index figures out at which index we need to look for a str
**	It verifies if it is within the valid range of min and max history nums
**	It sets his_index to a valid index in history or it returns failure
*/

static char	*tofind_negative(t_datahistory *history, int tofind)
{
	t_historyitem	*probe;
	int				i;

	i = -1;
	probe = history->tail;
	while (probe != NULL && i > tofind)
	{
		probe = probe->prev;
		i--;
	}
	if (i != tofind || probe == NULL)
		return (NULL);
	return (probe->str);
}

static char	*tofind_positive(t_datahistory *history, int tofind)
{
	t_historyitem	*probe;

	probe = history->tail;
	while (probe != NULL)
	{
		if (probe->number == tofind)
			return (probe->str);
		if (probe->number < tofind)
			return (NULL);
		probe = probe->prev;
	}
	return (NULL);
}

static char	*history_get_line_at_index(t_datahistory *history, int tofind)
{
	if (tofind < 0)
		return (tofind_negative(history, tofind));
	if (tofind > 0)
		return (tofind_positive(history, tofind));
	return (FUNCT_FAILURE);
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
