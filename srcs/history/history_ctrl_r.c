/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_ctrl_r.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/24 16:54:12 by omulder        #+#    #+#                */
/*   Updated: 2019/10/28 16:00:25 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	set_new_match(t_vshdata *data, char *match, char *full_str)
{
	char	*tmp;

	data->input->searchhistory.result_i = match - full_str;
	tmp = ft_strdup(full_str);
	if (tmp == NULL)
	{
		return (err_ret_prog_exit(E_N_ALLOC_STR, "reverse-i-search",
		EXIT_FAILURE));
	}
	ft_strdel(&data->input->searchhistory.result_str);
	data->input->searchhistory.result_str = tmp;
	return (FUNCT_SUCCESS);
}

static int	history_find_match(t_vshdata *data, char *to_match)
{
	t_historyitem	*probe;
	char			*match;

	probe = data->input->searchhistory.current;
	while (probe != NULL)
	{
		match = ft_strstr(probe->str, to_match);
		if (match != NULL)
			return (set_new_match(data, match, probe->str));
		probe = probe->prev;
		data->input->searchhistory.current = probe;
	}
	return (FUNCT_FAILURE);
}

/*
**  Search the history for a match with line, first checking the current
**  result_str, then checking from searchhistory.current back through the list.
**  When a match is found the string is set to result_str and the index
**  where the match starts is saved in result_i.
*/

int			history_ctrl_r(t_vshdata *data, bool second)
{
	char	*match;

	match = NULL;
	if (second == false)
	{
		if (data->input->searchhistory.result_str == NULL)
			return (FUNCT_FAILURE);
		match = ft_strstr(data->input->searchhistory.result_str,
		data->line->line);
	}
	if (match == NULL)
		return (history_find_match(data, data->line->line));
	else
	{
		return (set_new_match(data, match,
		data->input->searchhistory.result_str));
	}
	return (history_find_match(data, data->line->line));
}
