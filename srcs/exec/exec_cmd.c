/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:17:48 by omulder        #+#    #+#                */
/*   Updated: 2019/10/31 17:40:12 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <errno.h>
#include <sys/resource.h>

int			backup_stdfds(void)
{
	int				fd_num;
	int				fd_max;
	struct rlimit	rlp;
	struct stat		tmp;

	fd_num = 10;
	if (getrlimit(RLIMIT_NOFILE, &rlp) == -1 || rlp.rlim_cur < 10)
		return (FUNCT_ERROR);
	fd_max = rlp.rlim_cur;
	while (fstat(fd_num, &tmp) == -1 && errno != EBADF && fd_num <= fd_max)
		fd_num++;
	g_data->term_fd = fd_num;
	if (dup2(STDIN_FILENO, g_data->term_fd) == -1)
	{
		ft_eprintf(E_FAIL_DUP_FD);
		return (FUNCT_ERROR);
	}
	return (FUNCT_SUCCESS);
}

void		exec_cmd(char **args, t_vshdata *data)
{
	t_job *job;

	job = jobs_last_child(data->jobs->active_job);
	if (job == NULL)
		return ;
	jobs_update_job_command(job, args);
	jobs_add_process(job);
	if (job->last_proc == NULL)
		exit(1);
	job->last_proc->argv = args;
	if (g_data->exec_flags & EXEC_BG)
		job->bg = true;
	else
		job->bg = false;
	if (ft_strequ(job->last_proc->argv[0], "") == true)
		job->last_proc->no_cmd = true;
	if (exec_builtin(args, data) == false)
		exec_external(args, data);
}
