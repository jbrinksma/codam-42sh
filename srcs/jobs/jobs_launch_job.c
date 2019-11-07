/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_launch_job.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 13:02:41 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/11/06 11:09:22 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void		jobs_launch_job(t_job *job)
{
	int		fds[3];
	int		pipes[2];
	int		ret;

	fds[0] = STDIN_FILENO;
	fds[2] = STDERR_FILENO;
	ft_memset(pipes, UNINIT, sizeof(pipes));
	ret = jobs_launch_forked_job(job, fds, pipes);
	if (ret == FUNCT_FAILURE || ret == FUNCT_ERROR)
	{
		jobs_finished_job(job, true);
		return ;
	}
	jobs_add_job(g_data, job);
	if (job->bg == true)
		jobs_bg_job(job, false);
	else
		g_state->exit_code = jobs_fg_job(job, false);
}
