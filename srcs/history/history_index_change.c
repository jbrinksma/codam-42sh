/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_index_change.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/31 15:58:58 by omulder        #+#    #+#                */
/*   Updated: 2019/10/15 13:55:33 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int			history_index_change_up(t_datahistory *history)
{
	if (history->current == NULL)
	{
		if (history->tail != NULL)
		{
			history->current = history->tail;
			return (FUNCT_SUCCESS);
		}
		return (FUNCT_FAILURE);
	}
	if (history->current->prev == NULL)
		return (FUNCT_FAILURE);
	history->current = history->current->prev;
	return (FUNCT_SUCCESS);
}

int			history_index_change_down(t_datahistory *history)
{
	if (history->current == NULL)
		return (FUNCT_FAILURE);
	if (history->current->next == NULL)
		return (FUNCT_FAILURE);
	history->current = history->current->next;
	return (FUNCT_SUCCESS);
}
