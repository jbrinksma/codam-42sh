/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_fc_list.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/11 12:54:36 by omulder        #+#    #+#                */
/*   Updated: 2019/09/23 16:55:15 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**  You see the *end - 15? It's because normaly fc -l prints 16 history items.
**  So it's not magic, I just want 16 items.
*/

static void	find_start_end_no_param(t_datahistory *history, int *start,
int *end)
{
	*end = history->hist_start;
	*start = *end - 15;
	if (*start < 0 && history->history[0]->number != 1)
		*start = HISTORY_MAX + *start;
	else if (*start < 0)
		*start = 0;
}

static int	find_start_end(t_datahistory *history, t_fcdata *fc, int *start,
int *end)
{
	if (fc_find_index(history, fc, fc->first, start) == FUNCT_FAILURE)
		return (FUNCT_FAILURE);
	if (fc->last == NULL)
		*end = history->hist_start;
	else
	{
		if (fc_find_index(history, fc, fc->last, end) == FUNCT_FAILURE)
			return (FUNCT_FAILURE);
	}
	return (FUNCT_SUCCESS);
}

void		fc_list(t_datahistory *history, t_fcdata *fc)
{
	int start;
	int end;

	if (fc->first == NULL)
		find_start_end_no_param(history, &start, &end);
	else
	{
		if (find_start_end(history, fc, &start, &end) == FUNCT_FAILURE)
			return ;
	}
	if (fc->options & FC_OPT_R && fc->last == NULL)
		fc_print_reverse(start, end, history->history, fc);
	else if (history->history[start]->number > history->history[end]->number
	&& fc->last != NULL)
		fc_print_reverse(end, start, history->history, fc);
	else
		fc_print_regular(start, end, history->history, fc);
}
