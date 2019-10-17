/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_fc_list.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/11 12:54:36 by omulder        #+#    #+#                */
/*   Updated: 2019/10/17 14:58:04 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
** This function finds the history items needed when no parameters are given.
** It functions differently when option -l is given, because the list option
** has to display up to 16 items (usually 16, unless the history doesn't have 16
** items in it), while al other fc options will only display one item.
*/

static void	fc_find_start_len_no_param(t_datahistory *history, t_fcdata *fc,
t_historyitem **start, int *len)
{
	int i;

	i = 0;
	if (fc->options & FC_OPT_L)
	{
		*start = history->tail;
		*len = 16;
		while (*start != NULL && i < *len)
		{
			if ((*start)->prev == NULL)
				break ;
			*start = (*start)->prev;
			i++;
		}
	}
	else
	{
		*start = history->tail;
		*len = 1;
	}
}

/*
** This function finds the history items needed when one or two parameters are
** given (first and/or last).
** It works a little hacky, because I converted it from the array version. If
** you have suggestions for rewrite, please tell me.
**
** Fc_find_item finds the correct item for start, and if a second parameter is
** given, also for end. If we have just one parameter and the option is list, we
** find the amount of item untill the second to last item in the list. If the
** option is not -l, we only need one item.
**
** When we also have end, we have to know the count between start and end. The
** problem is that we don't know if end comes before or after start in the list.
** That's why if history_count fails the first time, we run it again but switch
** the parameters. This time it should succeed and we know that we have use the
** reverse printing function, so we set the reverse option.
**
** Lastly, in some cases the len variable can end up below zero, which we don't
** want so we return an error.
**
** TL;DR: It's crappy code. I'm sorry.
*/

static int	fc_find_start_len(t_datahistory *history, t_fcdata *fc,
t_historyitem **start, int *len)
{
	t_historyitem *end;

	if (fc_find_item(history, fc, fc->first, start) == FUNCT_FAILURE)
		return (FUNCT_FAILURE);
	if (fc->last == NULL && fc->options & FC_OPT_L && fc->options & ~FC_OPT_R)
		*len = history_count(*start, NULL);
	else if (fc->last == NULL && fc->options & FC_OPT_L)
		*len = history->count;
	else if (fc->last == NULL)
		*len = 1;
	else
	{
		if (fc_find_item(history, fc, fc->last, &end) == FUNCT_FAILURE)
			return (FUNCT_FAILURE);
		*len = history_count(*start, end);
		if (*len == -1)
		{
			*len = history_count(end, *start);
			fc->options |= FC_OPT_R;
		}
	}
	if (*len < 1)
	{
		ft_eprintf(E_FC_OUT_RANGE);
		return (FUNCT_FAILURE);
	}
	return (FUNCT_SUCCESS);
}

/*
** Just checks if any parameters are set to decided which function to use.
*/

int			fc_get_start(t_datahistory *history, t_fcdata *fc,
t_historyitem **start, int *len)
{
	if (fc->first == NULL)
		fc_find_start_len_no_param(history, fc, start, len);
	else
	{
		if (fc_find_start_len(history, fc, start, len) == FUNCT_FAILURE)
			return (FUNCT_FAILURE);
	}
	return (FUNCT_SUCCESS);
}

/*
** Check if we need to print in reverse, if so, print in reverse.
*/

void		fc_print(t_fcdata *fc, t_historyitem *start, int len)
{
	if (fc->options & FC_OPT_R)
		fc_print_reverse(start, len, fc);
	else
		fc_print_regular(start, len, fc);
}

/*
** First fc_get_start finds the start item and the amount of items to print.
** Then fc_print prints len items starting at start.
*/

void		fc_list(t_datahistory *history, t_fcdata *fc)
{
	t_historyitem	*start;
	int				len;
	char			*cmd;

	cmd = ft_strdup(history->tail->str);
	if (g_state->shell_type == SHELL_INTERACT)
		history_remove_tail(history);
	if (fc_get_start(history, fc, &start, &len) == FUNCT_FAILURE)
		return ;
	fc_print(fc, start, len);
	if (g_state->shell_type == SHELL_INTERACT)
		history_add_item(history, cmd);
	ft_strdel(&cmd);
	return ;
}
