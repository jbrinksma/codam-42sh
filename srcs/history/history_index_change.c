/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_index_change.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/31 15:58:58 by omulder        #+#    #+#                */
/*   Updated: 2019/07/31 16:01:11 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	index_history_first(t_inputdata *data)
{
	if (data->history[data->hist_index - 1]->str != NULL)
	{
		data->hist_first = false;
		data->hist_index -= 1;
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_FAILURE);
}

int			history_index_change_up(t_inputdata *data)
{
	if (data->hist_first)
		return (index_history_first(data));
	if (data->history[HISTORY_MAX - 1]->number == -1)
	{
		if (data->hist_index > 0 &&
		data->history[data->hist_index - 1]->str != NULL)
			data->hist_index -= 1;
		else
			return (FUNCT_FAILURE);
		return (FUNCT_SUCCESS);
	}
	else
	{
		if ((data->hist_index) - 1 == data->hist_start ||
		(data->hist_index == 0 && data->hist_start == HISTORY_MAX - 1))
			return (FUNCT_FAILURE);
		else if (data->hist_index > 0)
			data->hist_index -= 1;
		else if (data->hist_index == 0)
			data->hist_index = HISTORY_MAX - 1;
		return (FUNCT_SUCCESS);
	}
}

int			history_index_change_down(t_inputdata *data)
{
	if (data->hist_first)
		return (FUNCT_FAILURE);
	if (data->hist_index == data->hist_start)
	{
		data->hist_first = true;
		data->hist_index += 1;
		return (FUNCT_FAILURE);
	}
	if (data->history[HISTORY_MAX - 1]->number == -1)
	{
		if (data->hist_index < (HISTORY_MAX - 1) &&
		data->history[data->hist_index + 1]->str != NULL)
			data->hist_index += 1;
		else
			return (FUNCT_FAILURE);
		return (FUNCT_SUCCESS);
	}
	else
	{
		if (data->hist_index < (HISTORY_MAX - 1))
			data->hist_index += 1;
		else
			data->hist_index = 0;
		return (FUNCT_SUCCESS);
	}
}
