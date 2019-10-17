/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_match_line.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/12 12:44:34 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/15 14:09:48 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static char	*history_find_match(t_datahistory *history, char *match)
{
	t_historyitem	*probe;
	int				match_len;

	match_len = ft_strlen(match);
	probe = history->head;
	while (probe != NULL)
	{
		if (ft_strnequ(probe->str, match, match_len))
			return (probe->str);
		probe = probe->next;
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
