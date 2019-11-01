/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_notify.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/21 14:30:58 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/31 16:29:46 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

void		jobs_handle_finished_jobs(void)
{
	t_job	*job;

	job = g_data->jobs->joblist;
	while (job != NULL)
	{
		if (jobs_completed_job(job))
		{
			jobs_print_job_info(job, JOB_OPT_L, g_data->jobs->joblist);
			jobs_flush_job(jobs_remove_job(&g_data->jobs->joblist, job->pgid));
			job = g_data->jobs->joblist;
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
