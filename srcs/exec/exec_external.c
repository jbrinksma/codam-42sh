/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_external.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 10:47:19 by tde-jong       #+#    #+#                */
/*   Updated: 2019/11/04 16:12:48 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <sys/wait.h>

/*
**	Check if `char *binary` is valid.
**	Set termios structure to default values.
**	Run cmd_word, and wait for it to finish if the EXEC_WAIT flag is set.
**	Set termios structure back to our special values.
*/

static void		exec_bin(t_job *job, char **binary, t_vshdata *data)
{
	if (job->last_proc->no_cmd == false
		&& exec_validate_binary(*binary) == FUNCT_ERROR)
	{
		ft_strdel(binary);
		return ;
	}
	job->last_proc->binary = *binary;
	job->last_proc->redir_and_assign = data->current_redir_and_assign;
}

/*
**	Create the environment for the command about to be executed.
**	Use the cmd_word (see GRAMMAR) as binary name (+ optional relative path),
**	or if cmd_word contains one or more slashes ('/'), fetch the absolute path
**	from the PATH variable, and set `char *binary` equal to that instead.
**	Then: call `exec_bin`.
*/

void			exec_external(char **args, t_vshdata *data)
{
	t_job	*job;
	char	*binary;

	binary = ft_strdup(args[0]);
	if (binary == NULL)
	{
		ft_eprintf(E_ALLOC_STR);
		g_state->exit_code = EXIT_FAILURE;
		return ;
	}
	job = jobs_last_child(data->jobs->active_job);
	if (job->last_proc != NULL && job->last_proc->no_cmd == true)
		exec_bin(job, &binary, data);
	else if (ft_strchr(args[0], '/') == NULL)
	{
		ft_strdel(&binary);
		if (exec_find_binary(args[0], data, &binary) == FUNCT_SUCCESS)
			exec_bin(job, &binary, data);
		else
			ft_strdel(&binary);
	}
	else
		exec_bin(job, &binary, data);
}
