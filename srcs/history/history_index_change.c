/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_index_change.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/31 15:58:58 by omulder        #+#    #+#                */
/*   Updated: 2019/09/11 13:44:22 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	index_history_first(t_vshdata *data)
{
	if (data->history->history[data->history->hist_index - 1]->str != NULL)
	{
		data->history->hist_isfirst = false;
		data->history->hist_index -= 1;
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}

int			history_index_change_up(t_vshdata *data)
{
	if (data->history->hist_isfirst)
		return (index_history_first(data));
	if (data->history->history[HISTORY_MAX - 1]->number == -1)
	{
		if (data->history->hist_index > 0 &&
		data->history->history[data->history->hist_index - 1]->str != NULL)
			data->history->hist_index -= 1;
		else
			return (FUNCT_FAILURE);
		return (FUNCT_SUCCESS);
	}
	else
	{
		if ((data->history->hist_index) - 1 == data->history->hist_start ||
			(data->history->hist_index == 0 && data->history->hist_start
			== HISTORY_MAX - 1))
			return (FUNCT_FAILURE);
		else if (data->history->hist_index > 0)
			data->history->hist_index -= 1;
		else if (data->history->hist_index == 0)
			data->history->hist_index = HISTORY_MAX - 1;
		return (FUNCT_SUCCESS);
	}
}

int			history_index_change_down(t_vshdata *data)
{
	#ifdef DEBUG
	ft_eprintf("%i %i %i\n", data->history->hist_isfirst, data->history->hist_index, data->history->hist_start);
	#endif
	if (data->history->hist_isfirst)
		return (FUNCT_FAILURE);
	if (data->history->hist_index == data->history->hist_start)
	{
		data->history->hist_isfirst = true;
		data->history->hist_index += 1;
		return (FUNCT_FAILURE);
	}
	if (data->history->history[HISTORY_MAX - 1]->number == -1)
	{
		if (data->history->hist_index < (HISTORY_MAX - 1) &&
		data->history->history[data->history->hist_index + 1]->str != NULL)
			data->history->hist_index += 1;
		else
			return (FUNCT_FAILURE);
		return (FUNCT_SUCCESS);
	}
	else
	{
		if (data->history->hist_index < (HISTORY_MAX - 1))
			data->history->hist_index += 1;
		else
			data->history->hist_index = 0;
		return (FUNCT_SUCCESS);
	}
}
