/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_print.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/30 20:47:41 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/15 11:21:06 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include "libft.h"
#include <limits.h>

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
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	return (add_tabs(str, *new));
}

int			print_history_line(t_historyitem *item)
{
	int		ret;
	char	*tmp;

	ret = add_tabs_after_newlines(item->str, &tmp);
	if (ret == FUNCT_ERROR)
		return (FUNCT_FAILURE);
	ft_printf("%d\t%s\n", item->number, tmp);
	if (ret == true)
		ft_strdel(&tmp);
	return (FUNCT_SUCCESS);
}

void		history_print(t_datahistory *history)
{
	t_historyitem *probe;

	probe = history->head;
	while (probe != NULL)
	{
		if (print_history_line(probe) == FUNCT_ERROR)
			return ;
		probe = probe->next;
	}
}
