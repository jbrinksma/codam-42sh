/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_fc_substitute.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/21 15:22:42 by omulder        #+#    #+#                */
/*   Updated: 2019/10/17 14:58:20 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
** Finds the item, if there is no parameter it uses the last item in the list.
*/

static int	find_item(t_datahistory *history, t_fcdata *fc,
t_historyitem **item)
{
	if (fc->first == NULL)
		*item = history->tail;
	else
	{
		if (fc_find_item(history, fc, fc->first, item) == FUNCT_FAILURE)
			return (FUNCT_FAILURE);
	}
	if (*item == NULL)
	{
		ft_eprintf(E_FC_OUT_RANGE);
		return (FUNCT_FAILURE);
	}
	return (FUNCT_SUCCESS);
}

static int	replace_cmd(t_fcdata *fc, t_historyitem *item, char **cmd)
{
	char	*find;
	char	*replace;
	char	*tmp;

	find = NULL;
	replace = NULL;
	*cmd = ft_strjoin(item->str, "\n");
	if (*cmd == NULL)
		return (FUNCT_FAILURE);
	if (fc->replace != NULL)
	{
		replace = (ft_strchr(fc->replace, '=') + 1);
		if (replace == NULL)
			return (FUNCT_FAILURE);
		find = ft_strsub(fc->replace, 0, ((replace - 1) - fc->replace));
		if (find == NULL)
			return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
		tmp = ft_strreplace(*cmd, find, replace);
		ft_strdel(&find);
		if (tmp == NULL)
			return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
		ft_strdel(cmd);
		*cmd = tmp;
	}
	return (FUNCT_SUCCESS);
}

void		fc_substitute(t_vshdata *data, t_datahistory *history, t_fcdata *fc)
{
	t_historyitem	*item;
	char			*cmd;

	cmd = NULL;
	g_state->exit_code = EXIT_SUCCESS;
	if (g_state->shell_type == SHELL_INTERACT)
		history_remove_tail(history);
	if (find_item(history, fc, &item) == FUNCT_FAILURE ||
	replace_cmd(fc, item, &cmd) == FUNCT_ERROR)
	{
		ft_strdel(&cmd);
		g_state->exit_code = EXIT_FAILURE;
		return ;
	}
	ft_printf(cmd);
	data->fc_flags |= FC_SET_HIST;
	shell_one_line(data, cmd);
	data->fc_flags = 0;
	ft_strdel(&cmd);
}
