/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_status.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/21 11:25:18 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/31 17:21:14 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <sys/wait.h>

int			jobs_stopped_job(t_job *job)
{
	t_proc	*proc;

	if (job == NULL)
		return (FUNCT_FAILURE);
	proc = job->processes;
	if (proc == NULL)
		return (FUNCT_FAILURE);
	while (proc != NULL)
	{
		if (proc->state != PROC_STOPPED)
			return (FUNCT_FAILURE);
		proc = proc->next;
	}
	return (FUNCT_SUCCESS);
}

int			jobs_completed_job(t_job *job)
{
	t_proc *proc;

	if (job == NULL)
		return (FUNCT_SUCCESS);
	proc = job->processes;
	if (proc == NULL)
		return (FUNCT_SUCCESS);
	while (proc != NULL)
	{
		if (proc->state != PROC_COMPLETED)
			return (FUNCT_FAILURE);
		proc = proc->next;
	}
	return (FUNCT_SUCCESS);
}

void		jobs_update_pool_status(void)
{
	pid_t	pid;
	int		opt;
	int		status;

	status = 0;
	opt = WUNTRACED | WNOHANG | WCONTINUED;
	pid = waitpid(WAIT_ANY, &status, opt);
	while (jobs_mark_process_status(pid, status) == FUNCT_FAILURE)
		pid = waitpid(WAIT_ANY, &status, opt);
}
