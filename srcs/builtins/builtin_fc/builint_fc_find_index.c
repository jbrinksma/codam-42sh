/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builint_fc_find_index.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/12 18:16:01 by omulder        #+#    #+#                */
/*   Updated: 2019/09/23 16:20:56 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	find_history_item_str(t_datahistory *history, char *match,
int *index)
{
	int		i;
	size_t	len;

	i = history->hist_start;
	len = ft_strlen(match);
	while (i >= 0 && history->history[i]->str != NULL)
	{
		if (ft_strnequ(history->history[i]->str, match, len) == true)
		{
			*index = i;
			return (FUNCT_SUCCESS);
		}
		i--;
	}
	i = (HISTORY_MAX - 1);
	while (i > history->hist_start && history->history[i]->str != NULL)
	{
		if (ft_strnequ(history->history[i]->str, match, len) == true)
		{
			*index = i;
			return (FUNCT_SUCCESS);
		}
		i--;
	}
	return (FUNCT_FAILURE);
}

static void	find_history_item_num(t_datahistory *history, int num, int *index)
{
	int i;

	i = history->hist_start;
	while (i >= 0 && history->history[i]->str != NULL)
	{
		if (history->history[i]->number == num)
		{
			*index = i;
			return ;
		}
		i--;
	}
	i = (HISTORY_MAX - 1);
	while (i >= history->hist_start && history->history[i]->str != NULL)
	{
		if (history->history[i]->number == num)
		{
			*index = i;
			return ;
		}
		i--;
	}
	*index = history->hist_start;
}

static void	find_hist_num_neg(t_datahistory *history, int num, int *index)
{
	int total;

	total = history->history[history->hist_start]->number;
	if (num == 0 || num == -1)
		*index = history->hist_start;
	if (num == 0 || num == -1)
		return ;
	if (num < 0)
		num = total + 1 + num;
	if (num <= 0)
	{
		if (total < HISTORY_MAX)
			*index = 0;
		else
		{
			if (history->hist_start == (HISTORY_MAX - 1))
				*index = 0;
			else if (total > history->history[history->hist_start + 1]->number)
				*index = history->hist_start + 1;
			else
				*index = history->hist_start + 2;
		}
		return ;
	}
	*index = (num - 1) % HISTORY_MAX;
}

int			fc_find_index(t_datahistory *history, t_fcdata *fc,
char *str, int *index)
{
	int	num;

	num = 0;
	if (ft_isdigit(str[0]) || ((str[0] == '+' || str[0] == '-') &&
	ft_isdigit(str[1])))
	{
		num = ft_atoi(str);
		if (str == fc->first && num <= 0)
			fc->options |= FC_FIRST_NEG;
		else if (str == fc->last && num <= 0)
			fc->options |= FC_LAST_NEG;
		if (num <= 0)
			find_hist_num_neg(history, num, index);
		else
			find_history_item_num(history, num, index);
	}
	else
	{
		if (find_history_item_str(history, str, index) == FUNCT_FAILURE)
		{
			err_void_exit(E_FC_OUT_RANGE, EXIT_FAILURE);
			return (FUNCT_FAILURE);
		}
	}
	return (FUNCT_SUCCESS);
}
