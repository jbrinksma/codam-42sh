/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_helpers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 15:11:11 by omulder        #+#    #+#                */
/*   Updated: 2019/10/17 16:22:10 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
** Removes the last item in the history list.
*/

void			history_remove_tail(t_datahistory *history)
{
	t_historyitem *tofree;

	if (history == NULL || history->tail == NULL)
		return ;
	tofree = history->tail;
	if (history->head == history->tail)
		history->head = NULL;
	history->tail = history->tail->prev;
	if (history->tail != NULL)
		history->tail->next = NULL;
	history_free_item(&tofree);
	history->count -= 1;
}

/*
** Removes the first item in the history list.
*/

void			history_remove_head(t_datahistory *history)
{
	t_historyitem *tofree;

	if (history == NULL || history->head == NULL)
		return ;
	tofree = history->head;
	if (history->head == history->tail)
		history->tail = NULL;
	history->head = history->head->next;
	if (history->head != NULL)
		history->head->prev = NULL;
	history_free_item(&tofree);
	history->count -= 1;
}

/*
** Counts the items from start -> end. If end is NULL, counts till end of
** the list. If end is not found, returns -1.
*/

int				history_count(t_historyitem *start, t_historyitem *end)
{
	t_historyitem	*probe;
	int				count;

	count = 1;
	probe = start;
	while (probe != end && probe != NULL)
	{
		count++;
		probe = probe->next;
	}
	if (probe != end)
		return (-1);
	return (count);
}
