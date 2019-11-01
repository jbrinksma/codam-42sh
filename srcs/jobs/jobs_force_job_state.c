/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_force_job_state.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 16:03:38 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/31 16:05:01 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	jobs_force_job_state(t_job *job, t_proc_state state)
{
	t_proc *proc;

	proc = job->processes;
	while (proc != NULL)
	{
		proc->state = state;
		proc = proc->next;
	}
}
