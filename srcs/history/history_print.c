/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_print.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/30 20:47:41 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/26 15:33:31 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include "libft.h"

/*
** Print the history
*/

static int	add_tabs(char *str, char *new)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		new[j] = str[i];
		if (str[i] == '\n' && str[i + 1] != '\0')
		{
			j++;
			new[j] = '\t';
		}
		i++;
		j++;
	}
	return (true);
}

static int	add_tabs_after_newlines(char *str, char **new)
{
	int		i;
	int		tab_count;

	i = 0;
	tab_count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n' && str[i + 1] != '\0')
			tab_count++;
		i++;
	}
	if (tab_count == 0)
	{
		*new = str;
		return (false);
	}
	*new = ft_strnew(i + tab_count);
	if (*new == NULL)
		return (false);
	return (add_tabs(str, *new));
}

static void	find_start(t_history **history, int *start)
{
	int		i;
	int		smallest;

	i = 0;
	smallest = HISTORY_MAX + 1;
	while (i < HISTORY_MAX && history[i]->str != NULL)
	{
		if (history[i]->number < smallest)
		{
			*start = i;
			smallest = history[i]->number;
		}
		i++;
	}
}

void		print_history_line(t_history *history)
{
	int		ret;
	char	*tmp;

	ret = add_tabs_after_newlines(history->str, &tmp);
	ft_printf("%d\t%s\n", history->number, tmp);
	if (ret == true)
		ft_strdel(&tmp);
}

void		history_print(t_history **history)
{
	int		i;
	int		start;

	find_start(history, &start);
	i = start;
	while (i < HISTORY_MAX && history[i]->str != NULL)
	{
		print_history_line(history[i]);
		i++;
	}
	i = 0;
	while (start != 0 && i < start && history[i]->str != NULL)
	{
		print_history_line(history[i]);
		i++;
	}
}
