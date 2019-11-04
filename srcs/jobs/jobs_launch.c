/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_launch.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 16:25:10 by rkuijper       #+#    #+#                */
/*   Updated: 2019/11/04 11:45:28 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include "signal.h"
#include <unistd.h>

static void	setup_stds(t_proc *proc, int fds[3], int pipes[2])
{
	if (proc->next != NULL)
	{
		if (pipe(pipes) < 0)
		{
			ft_eprintf("Could not pipe.\n");
			exit(1);
		}
		fds[1] = pipes[1];
	}
	else
		fds[1] = STDOUT_FILENO;
}

static void	cleanup_after_proc(t_proc *proc, int fds[3], int pipes[2])
{
	if (fds[0] != STDIN_FILENO && fds[0] != UNINIT)
		close(fds[0]);
	if (fds[1] != STDOUT_FILENO && fds[1] != UNINIT)
		close(fds[1]);
	fds[0] = pipes[0];
	if (proc->binary != NULL)
		ft_strdel(&proc->binary);
	if (proc->argv != NULL)
		ft_strarrdel(&proc->argv);
	if (proc->env)
		ft_memdel((void**)&proc->env);
}

static void	setup_fork(t_job *job, t_proc *proc, int fds[3], int pipes[2])
{
	if (proc->pid < 0)
	{
		ft_eprintf("Could not fork.\n");
		exit(1);
	}
	if (proc->pid == 0)
		jobs_launch_proc(job, proc, fds, pipes);
	else
	{
		if (g_state->shell_type == SHELL_INTERACT)
		{
			if (job->pgid == 0)
				job->pgid = proc->pid;
			setpgid(proc->pid, job->pgid);
		}
	}
}

static int	launch_forked_job(t_job *job, int fds[3], int pipes[2])
{
	pid_t	pid;
	t_proc	*proc;

	proc = job->processes;
	while (proc != NULL)
	{
		if (proc->is_builtin == false && proc->binary == NULL)
		{
			jobs_flush_job(job);
			g_state->exit_code = 1;
			return (FUNCT_FAILURE);
		}
		setup_stds(proc, fds, pipes);
		pid = fork();
		proc->pid = pid;
		setup_fork(job, proc, fds, pipes);
		cleanup_after_proc(proc, fds, pipes);
		proc = proc->next;
	}
	return (FUNCT_SUCCESS);
}

void		jobs_launch_job(t_job *job)
{
	int		fds[3];
	int		pipes[2];

	fds[0] = STDIN_FILENO;
	fds[2] = STDERR_FILENO;
	ft_memset(pipes, UNINIT, sizeof(pipes));
	if (job->bg == false && jobs_exec_is_single_builtin_proc(job->processes))
	{
		jobs_exec_builtin(job->processes);
		env_remove_tmp(g_data->envlst);
		jobs_finished_job(job, true);
		return ;
	}
	if (launch_forked_job(job, fds, pipes) == FUNCT_FAILURE)
		return ;
	jobs_add_job(g_data, job);
	if (job->bg == true)
		jobs_bg_job(job, false);
	else
		g_state->exit_code = jobs_fg_job(job, false);
}
