/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_notify.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/21 14:30:58 by rkuijper       #+#    #+#                */
/*   Updated: 2019/11/07 16:42:33 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	jobs_handle_finished_jobs(void)
{
	t_job	*job;
	t_job	*tmp;

	job = g_data->jobs->joblist;
	while (job != NULL)
	{
		if (jobs_completed_job(job))
		{
			tmp = job->next;
			jobs_print_job_info(job, JOB_OPT_L, g_data->jobs->joblist);
			jobs_flush_job(jobs_remove_job(&g_data->jobs->joblist, job->pgid));
			job = tmp;
		}
		else
			job = job->next;
	}
}

void		jobs_notify_pool(void)
{
	jobs_update_pool_status();
	jobs_handle_finished_jobs();
}
