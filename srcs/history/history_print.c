/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_print.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/30 20:47:41 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/02 09:49:13 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include "libft.h"

/*
** Print the history
*/

static void	find_start(t_history **history, int *smallest, int *start)
{
	int i;

	i = 0;
	*smallest = HISTORY_MAX + 1;
	while (i < HISTORY_MAX && history[i]->str != NULL)
	{
		if (history[i]->number < *smallest)
		{
			*start = i;
			*smallest = history[i]->number;
		}
		i++;
	}
}

void		history_print(t_history **history)
{
	int i;
	int	smallest;
	int start;

	find_start(history, &smallest, &start);
	i = start;
	while (i < HISTORY_MAX && history[i]->str != NULL)
	{
		ft_printf("%5d  %s\n", history[i]->number, history[i]->str);
		i++;
	}
	i = 0;
	while (start != 0 && i < start && history[i]->str != NULL)
	{
		ft_printf("%5d  %s\n", history[i]->number, history[i]->str);
		i++;
	}
}
