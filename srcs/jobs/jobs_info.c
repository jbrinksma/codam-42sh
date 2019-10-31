/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_info.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/18 16:48:34 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/30 16:11:48 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static char		*g_proc_state_string[] =
{
	[PROC_RUNNING] = "running\t",
	[PROC_STOPPED] = "suspended\t",
	[PROC_CONTINUED] = "continued\t",
	[PROC_COMPLETED] = "done\t\t"
};

static bool		is_current_job(t_job *job, t_job *joblist)
{
	if (jobs_find_current_job(joblist) == job)
		return (true);
	return (false);
}

static bool		is_previous_job(t_job *job, t_job *joblist)
{
	if (jobs_find_previous_job(joblist) == job && job->next != NULL)
		return (true);
	return (false);
}

static void		print_process_data(t_job *job)
{
	t_proc *proc;

	proc = job->processes;
	if (proc == 0)
		return (ft_putchar('\n'));
	while (proc != NULL)
	{
		ft_printf("\t- %d %s\n", proc->pid, g_proc_state_string[proc->state]);
		proc = proc->next;
	}
}

void			jobs_print_job_info(t_job *job, int options, t_job *joblist)
{
	int	current;

	if (job->bg == false)
		return ;
	current = ' ';
	if (is_current_job(job, joblist))
		current = '+';
	if (is_previous_job(job, joblist))
		current = '-';
	ft_printf("[%i]%c %s\n", job->job_id, current, job->command);
	if (options & (JOB_OPT_L | JOB_OPT_P))
		print_process_data(job);
}
