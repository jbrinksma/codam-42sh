/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:17:48 by omulder        #+#    #+#                */
/*   Updated: 2019/10/05 09:51:17 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	The `pipes` struct contains the file descriptors of the pipe leading up to
**	the simple_command (see GRAMMAR), and the file descriptors of the pipe which
**	the simple_command will output into.
**
**	If the `cmd` is not part of a pipeline, or the `cmd` is the last command
**	in the pipeline, we run it in the foreground. Otherwise, it gets
**	executed in the background.
*/

void		exec_cmd(char **args, t_vshdata *data, t_pipes pipes)
{
	if (args[0][0] != '\0' && exec_builtin(args, data) == false)
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
