/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_launch_forked_job.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 16:25:10 by rkuijper       #+#    #+#                */
/*   Updated: 2019/11/06 11:09:19 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include "signal.h"
#include <unistd.h>

static void	setup_fork(t_job *job, t_proc *proc, int fds[3], int pipes[2])
{
	if (proc->pid < 0)
	{
		ft_eprintf(E_FORK_STR);
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

static int	prepare_arguments_proc(t_ast *node, t_proc *proc, char ***argv)
{
	if (expan_handle_variables(node, g_data->envlst) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	if (node->type == WORD && expan_pathname(node) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	exec_quote_remove(node);
	if (node->type == WORD)
		proc->redir_and_assign = node->right;
	else
		proc->redir_and_assign = node;
	*argv = exec_create_process_args(node);
	if (*argv == NULL)
	{
		ft_eprintf(E_N_ALLOC_STR, "process");
		return (FUNCT_ERROR);
	}
	return (FUNCT_SUCCESS);
}

static int	prepare_settings_proc(t_job *job, t_proc *proc, char **argv)
{
	proc->argv = argv;
	if (ft_strequ(proc->argv[0], "") == true)
		proc->no_cmd = true;
	if (proc->no_cmd == true && exec_assigns(proc->redir_and_assign,
		g_data, ENV_LOCAL) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	jobs_update_job_command(job, argv);
	if (exec_builtin(argv, proc) == false)
		exec_external(argv, g_data, proc);
	return (FUNCT_SUCCESS);
}

static int	handle_nonforked_builtin(t_job *job)
{
	if (job->bg == false && jobs_exec_is_single_builtin_proc(job->processes))
	{
		jobs_exec_builtin(job->processes);
		env_remove_tmp(g_data->envlst);
		return (FUNCT_FAILURE);
	}
	return (FUNCT_SUCCESS);
}

int			jobs_launch_forked_job(t_job *job, int fds[3], int pipes[2])
{
	pid_t	pid;
	t_proc	*proc;
	char	**argv;
	t_ast	*node;

	proc = job->processes;
	while (proc != NULL)
	{
		argv = NULL;
		node = proc->node;
		if (prepare_arguments_proc(node, proc, &argv) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		if (prepare_settings_proc(job, proc, argv) == FUNCT_ERROR)
			return (FUNCT_ERROR);
		if (handle_nonforked_builtin(job) != FUNCT_SUCCESS)
			return (FUNCT_ERROR);
		jobs_launch_setup_stds(proc, fds, pipes);
		pid = fork();
		proc->pid = pid;
		setup_fork(job, proc, fds, pipes);
		jobs_launch_cleanup_after_proc(proc, fds, pipes);
		proc = proc->next;
	}
	return (FUNCT_SUCCESS);
}
