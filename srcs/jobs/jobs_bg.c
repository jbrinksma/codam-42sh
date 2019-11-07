/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_bg.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/18 16:46:22 by rkuijper       #+#    #+#                */
/*   Updated: 2019/11/07 13:54:56 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <signal.h>

void	jobs_bg_job(t_job *job, bool job_continued)
{
	job->bg = true;
	if (job_continued && kill(-job->pgid, SIGCONT) < 0)
		ft_eprintf("kill (SIGCONT): failed\n");
	jobs_print_job_info(job, JOB_OPT_L, g_data->jobs->joblist);
}
