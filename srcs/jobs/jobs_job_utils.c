/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_job_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 10:47:19 by tde-jong       #+#    #+#                */
/*   Updated: 2019/10/30 17:25:48 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <sys/wait.h>

int		jobs_get_job_state(t_job *job)
{
	int		status;
	pid_t	result;

	result = waitpid(-job->pgid, &status, WNOHANG);
	if (WIFSTOPPED(status))
		return (JOB_SUSPEND);
	if (WIFCONTINUED(status))
		return (JOB_RUNNING);
	if (result != 0)
		return (JOB_EXIT);
	return (JOB_RUNNING);
}

t_job	*jobs_find_current_job(t_job *joblist)
{
	t_job *job;
	t_job *toreturn;

	job = joblist;
	toreturn = job;
	while (job != NULL)
	{
		if (job->current > toreturn->current)
			toreturn = job;
		job = job->next;
	}
	return (toreturn);
}
