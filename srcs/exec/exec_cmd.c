/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:17:48 by omulder        #+#    #+#                */
/*   Updated: 2019/11/05 13:29:52 by jbrinksm      ########   odam.nl         */
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

void		exec_cmd(t_vshdata *data)
{
	t_job *job;

	job = jobs_last_child(data->jobs->active_job);
	if (job == NULL)
		return ;
	jobs_add_process(job);
	if (job->last_proc == NULL)
		exit(1);
	job->last_proc->node = data->cur_node;
	if (g_data->exec_flags & EXEC_BG)
		job->bg = true;
	else
		job->bg = false;
}
