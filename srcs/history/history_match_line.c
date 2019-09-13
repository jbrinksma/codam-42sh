/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_match_line.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/12 12:44:34 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/12 15:01:36 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static char	*history_find_match(t_datahistory *history, char *match)
{
	int i;
	int	match_len;

	match_len = ft_strlen(match);
	i = history->hist_start;
	while (i >= 0 && history->history[i]->str != NULL)
	{
		if (ft_strncmp(history->history[i]->str, match, match_len) == 0)
			return (history->history[i]->str);
		i--;
	}
	i = (HISTORY_MAX - 1);
	while (i > history->hist_start && history->history[i]->str != NULL)
	{
		if (ft_strncmp(history->history[i]->str, match, match_len) == 0)
			return (history->history[i]->str);
		i--;
	}
	return (NULL);
}

static char	*history_get_match(char *line, size_t i)
{
	int		match_len;
	char	*match;

	match_len = 0;
	i++;
	while (line[i] != '\0' && ft_isblank(line[i]) == false && line[i] != '\n')
	{
		match_len++;
		i++;
	}
	match = ft_strndup(&line[i - match_len], match_len);
	if (match == NULL)
		ft_eprintf(E_ALLOC_STR);
	return (match);
}

char		*history_match_line(t_datahistory *history, char *line, size_t i)
{
	char	*match;
	char	*his_line;

	match = history_get_match(line, i);
	if (match == NULL)
		return (NULL);
	his_line = history_find_match(history, match);
	if (his_line == NULL)
		ft_eprintf(E_HIST_NOT_FOUND, match);
	ft_strdel(&match);
	return (his_line);
}
