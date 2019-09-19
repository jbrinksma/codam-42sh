/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:17:48 by omulder        #+#    #+#                */
/*   Updated: 2019/09/16 09:54:40 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void		exec_cmd(char **args, t_vshdata *data, t_pipes pipes)
{
	if (exec_builtin(args, data) == false)
	{
		if (pipes.currentpipe[0] == PIPE_UNINIT
		&& pipes.currentpipe[1] == PIPE_UNINIT
		&& pipes.parentpipe[0] == PIPE_UNINIT
		&& pipes.parentpipe[1] == PIPE_UNINIT)
			data->exec_flags &= ~EXEC_ISPIPED;
		else
			data->exec_flags |= EXEC_ISPIPED;
		if (pipes.pipeside == PIPE_UNINIT || (pipes.pipeside == PIPE_EXTEND
		&& pipes.currentpipe[0] != PIPE_UNINIT
		&& pipes.currentpipe[1] != PIPE_UNINIT
		&& pipes.parentpipe[0] == PIPE_UNINIT
		&& pipes.parentpipe[1] == PIPE_UNINIT))
			data->exec_flags |= EXEC_WAIT;
		else
			data->exec_flags &= ~EXEC_WAIT;
		exec_external(args, data);
	}
	ft_strarrdel(&args);
	env_remove_tmp(data->envlst);
}
