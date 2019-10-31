/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_fg.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/22 14:27:21 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/30 18:11:26 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	read_options(char **av)
{
	if (av[1] == NULL || av[1][0] != '-')
		return (FUNCT_SUCCESS);
	else
	{
		ft_eprintf(E_FG_USAGE, av[1][1]);
		return (FUNCT_ERROR);
	}
}

static void	fg(t_job *job)
{
	t_proc *proc;

	jobs_remove_job(&g_data->jobs->joblist, job->pgid);
	if (jobs_stopped_job(job))
		jobs_continue_job(job, true);
	else
	{
		proc = job->processes;
		while (proc != NULL)
		{
			proc->state = PROC_RUNNING;
			proc = proc->next;
		}
		jobs_print_job_info(job, JOB_OPT_L, g_data->jobs->joblist);
		jobs_fg_job(job, 0);
	}
}

void		builtin_fg(char **av, t_vshdata *data)
{
	t_job	*job;

	g_state->exit_code = EXIT_FAILURE;
	if (read_options(av) == FUNCT_ERROR)
		return ;
	if (av[1] == NULL)
		job = jobs_find_job("%%", data->jobs->joblist);
	else
		job = jobs_find_job(av[1], data->jobs->joblist);
	if (job == NULL)
	{
		ft_eprintf(E_FG_NO_CUR);
		return ;
	}
	fg(job);
}
