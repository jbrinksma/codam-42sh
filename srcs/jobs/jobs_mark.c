/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_mark.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/21 11:51:41 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/31 13:50:03 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <signal.h>

int			jobs_mark_proc(t_proc *proc, int status)
{
	if (WIFSTOPPED(status))
	{
		proc->exit_status = 0;
		proc->state = PROC_STOPPED;
	}
	else
	{
		proc->exit_status = status;
		proc->state = PROC_COMPLETED;
		if (WIFEXITED(status))
			proc->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) && WTERMSIG(status) != SIGINT)
		{
			if (WTERMSIG(status) != SIGPIPE)
				ft_eprintf(E_JOB_MARK_SIG, (int)proc->pid,
					WTERMSIG(status));
			proc->exit_status = 1;
		}
		else if (WTERMSIG(status) == SIGINT)
			proc->exit_status = 130;
	}
	return (0);
}

int			jobs_mark_job(t_job *job, pid_t pid, int status)
{
	t_proc	*proc;

	if (pid > 0)
	{
		proc = job->processes;
		while (proc)
		{
			if (proc->pid == pid)
				return (jobs_mark_proc(proc, status));
			proc = proc->next;
		}
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_SUCCESS);
}

int			jobs_mark_pool(pid_t pid, int status)
{
	t_job	*job;
	t_proc	*proc;

	if (pid > 0)
	{
		job = g_data->jobs->joblist;
		while (job != NULL)
		{
			proc = job->processes;
			while (proc != NULL)
			{
				if (proc->pid == pid)
				{
					jobs_mark_proc(proc, status);
					if (job->bg == false && proc->state == PROC_STOPPED)
						job->bg = true;
				}
				proc = proc->next;
			}
			job = job->next;
		}
		return (FUNCT_SUCCESS);
	}
	return (FUNCT_SUCCESS);
}
