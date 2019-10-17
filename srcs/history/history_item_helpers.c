/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_item_helpers.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/15 10:16:47 by omulder        #+#    #+#                */
/*   Updated: 2019/10/17 16:24:55 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static t_historyitem	*history_new_item(char *line)
{
	t_historyitem	*new;
	size_t			len;

	new = ft_memalloc(sizeof(t_historyitem));
	if (new == NULL)
	{
		ft_eprintf(E_N_ALLOC_STR, "history");
		return (NULL);
	}
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len -= 1;
	new->str = ft_strndup(line, len);
	if (new->str == NULL)
	{
		ft_eprintf(E_N_ALLOC_STR, "history");
		return (NULL);
	}
	return (new);
}

void					history_free_item(t_historyitem **item)
{
	ft_strdel(&((*item)->str));
	ft_memdel((void**)item);
}

static bool				history_is_duplicate(t_datahistory *history, char *line)
{
	size_t	len;

	if (history->tail == NULL)
		return (false);
	len = ft_strlen(line);
	if (line[0] == '\0' || (line[0] == '\n' && line[1] == '\0'))
		return (true);
	if (line[len - 1] == '\n')
		len -= 1;
	if (ft_strnequ(history->tail->str, line, len) == true
		&& history->tail->str[len] == '\0')
		return (true);
	return (false);
}

int						history_add_item(t_datahistory *history, char *line)
{
	t_historyitem *new;

	if (history_is_duplicate(history, line))
		return (FUNCT_FAILURE);
	new = history_new_item(line);
	if (new == NULL)
		return (FUNCT_ERROR);
	if (history->head == NULL && history->tail == NULL)
	{
		new->number = 1;
		history->head = new;
	}
	else
	{
		new->number = history->tail->number + 1;
		new->prev = history->tail;
		history->tail->next = new;
	}
	history->tail = new;
	history->count += 1;
	while (history->count > history_get_histsize())
		history_remove_head(history);
	return (FUNCT_SUCCESS);
}
