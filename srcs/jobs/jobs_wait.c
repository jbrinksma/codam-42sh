/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_wait.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/21 11:22:46 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/31 13:43:15 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

void		jobs_wait_job(t_job *job)
{
	if (job->pgid == 0)
		return ;
	while (!jobs_stopped_job(job) && !jobs_completed_job(job))
		;
}
