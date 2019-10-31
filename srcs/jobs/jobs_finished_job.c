/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_finished_job.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 09:39:34 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/31 09:43:49 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void		jobs_finished_job(t_job *job, bool check)
{
	t_job *child;

	if (job == NULL)
		return ;
	jobs_remove_job(&g_data->jobs->joblist, job->pgid);
	child = job->child;
	if (check && job->child != NULL &&
		(job->andor == ANDOR_NONE ||
		(job->andor == ANDOR_AND && g_state->exit_code == 0) ||
		(job->andor == ANDOR_OR && g_state->exit_code != 0)))
	{
		jobs_flush_job(job);
		jobs_launch_job(child);
		return ;
	}
	else if (child != NULL)
		jobs_finished_job(child, false);
	jobs_flush_job(job);
}
