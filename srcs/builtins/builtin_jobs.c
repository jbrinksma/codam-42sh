/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_jobs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 14:03:16 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/31 11:51:27 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int				builtin_jobs_new_current_val(t_job *joblist)
{
	t_job *job;

	job = jobs_find_current_job(joblist);
	if (job == NULL)
		return (0);
	else
		return (job->current + 1);
}

static int		read_options(char **args, int *arg, int *options)
{
	int i;

	while (args[*arg] != NULL && *args[*arg] == '-')
	{
		i = 1;
		while (args[*arg][i] != '\0')
		{
			if (args[*arg][i] == 'p')
				*options |= JOB_OPT_P;
			else if (args[*arg][i] == 'l')
				*options |= JOB_OPT_L;
			else
			{
				ft_eprintf(E_JOBS_USAGE, args[*arg][i]);
				return (FUNCT_ERROR);
			}
			i++;
		}
		(*arg)++;
	}
	return (FUNCT_SUCCESS);
}

static int		jobs_log_args(t_datajobs *jobs, int options, char **args)
{
	int		i;
	t_job	*toprint;

	if (jobs->joblist == NULL)
	{
		ft_eprintf(E_JOBS_NO_JOB, args[0]);
		return (FUNCT_ERROR);
	}
	i = 0;
	while (args[i] != NULL)
	{
		toprint = jobs_find_job(args[i], jobs->joblist);
		if (toprint == NULL)
			return (FUNCT_FAILURE);
		jobs_print_job_info(toprint, options, jobs->joblist);
		i++;
	}
	return (FUNCT_SUCCESS);
}

static void		jobs_log_all(t_datajobs *jobs, int options)
{
	t_job *job;

	job = jobs->joblist;
	while (job != NULL)
	{
		if (job->pgid == 0)
		{
			job = job->next;
			continue ;
		}
		jobs_print_job_info(job, options, jobs->joblist);
		job = job->next;
	}
}

void			builtin_jobs(char **args, t_vshdata *data)
{
	int	arg;
	int options;

	arg = 1;
	options = JOB_OPT_NONE;
	g_state->exit_code = EXIT_FAILURE;
	if (read_options(args, &arg, &options) != FUNCT_SUCCESS)
		return ;
	jobs_handle_finished_jobs();
	if (args[arg] != NULL)
	{
		if (jobs_log_args(data->jobs, options, args + arg) == FUNCT_ERROR)
			return ;
	}
	else
		jobs_log_all(data->jobs, options);
	g_state->exit_code = EXIT_SUCCESS;
}
