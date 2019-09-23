/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_fc_print_helpers.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/11 13:03:14 by omulder        #+#    #+#                */
/*   Updated: 2019/09/23 16:06:08 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

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

int			fc_list_print_line(t_history *history, t_fcdata *fc)
{
	int		ret;
	char	*tmp;

	ret = add_tabs_after_newlines(history->str, &tmp);
	if (ret == FUNCT_ERROR)
		return (FUNCT_FAILURE);
	if (fc->options & FC_OPT_N)
		ft_printf("\t%s\n", tmp);
	else
		ft_printf("%d\t%s\n", history->number, tmp);
	if (ret == true)
		ft_strdel(&tmp);
	return (FUNCT_SUCCESS);
}

/*
** Start and end have to be valid indexes on the history_array
*/

void		fc_print_regular(int start, int end, t_history **history,
t_fcdata *fc)
{
	int i;

	i = 0;
	while ((start + i) < HISTORY_MAX &&
	((end >= start && (start + i) <= end) || end < start) &&
	history[start + i]->str != NULL)
	{
		if (fc_list_print_line(history[(start + i)], fc) == FUNCT_FAILURE)
			return ;
		i++;
	}
	if ((start + i) >= HISTORY_MAX && end < start)
	{
		i = 0;
		while (i <= end && history[i]->str != NULL)
		{
			if (fc_list_print_line(history[i], fc) == FUNCT_FAILURE)
				return ;
			i++;
		}
	}
}

/*
** Start and end have to be valid indexes on the history_array.
** The function will start printing at end and will decrement untill it reaches
** start. This is counterintuitive but hey it says reverse so....
*/

void		fc_print_reverse(int start, int end, t_history **history,
t_fcdata *fc)
{
	int i;

	i = 0;
	while ((end - i) >= 0 &&
	((end - i) >= start || start > end) &&
	history[end - i]->str != NULL)
	{
		if (fc_list_print_line(history[end - i], fc) == FUNCT_FAILURE)
			return ;
		i++;
	}
	if ((end - i) <= 0 && start > end)
	{
		i = HISTORY_MAX - 1;
		while (i >= start && history[i]->str != NULL)
		{
			if (fc_list_print_line(history[i], fc) == FUNCT_FAILURE)
				return ;
			i--;
		}
	}
}
