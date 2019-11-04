/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_wait.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/21 11:22:46 by rkuijper       #+#    #+#                */
/*   Updated: 2019/11/04 12:54:06 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <sys/wait.h>
#include <signal.h>

int		jobs_wait_job(t_job *job, int wait_opt)
{
	pid_t	pid;
	int		status;

	if (job == NULL)
		return (0);
	pid = waitpid(WAIT_ANY, &status, wait_opt);
	while (jobs_mark_process_status(pid, status) == FUNCT_FAILURE &&
		jobs_stopped_job(job) == FUNCT_FAILURE &&
		jobs_completed_job(job) == FUNCT_FAILURE)
		pid = waitpid(WAIT_ANY, &status, wait_opt);
	return (status);
}
