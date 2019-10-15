/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_fc_substitute.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/21 15:22:42 by omulder        #+#    #+#                */
/*   Updated: 2019/10/11 12:38:22 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	find_index(t_datahistory *history, t_fcdata *fc, int *index)
{
	if (fc->first == NULL)
		*index = history->hist_start;
	else
	{
		if (fc_find_index(history, fc, fc->first, index) == FUNCT_FAILURE)
			return (FUNCT_FAILURE);
	}
	return (FUNCT_SUCCESS);
}

static int	replace_cmd(t_datahistory *history, t_fcdata *fc, int index,
char **cmd)
{
	char	*find;
	char	*replace;
	char	*tmp;

	find = NULL;
	replace = NULL;
	*cmd = ft_strjoin(history->history[index]->str, "\n");
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
	int		index;
	char	*cmd;

	index = 0;
	cmd = NULL;
	if (find_index(history, fc, &index) == FUNCT_FAILURE ||
	replace_cmd(history, fc, index, &cmd) == FUNCT_ERROR)
	{
		ft_strdel(&cmd);
		return ;
	}
	history_replace_last(history->history, &cmd);
	ft_printf(cmd);
	shell_one_line(data, cmd);
	g_state->exit_code = EXIT_SUCCESS;
	ft_strdel(&cmd);
}
