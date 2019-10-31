/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_flush.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/22 13:22:46 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/22 13:24:44 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <signal.h>

void		jobs_flush_all(void)
{
	t_job *tmp;
	t_job *job;

	job = g_data->jobs->joblist;
	while (job != NULL)
	{
		kill(-job->pgid, SIGKILL);
		tmp = job;
		job = job->next;
		ft_strdel(tmp->command);
		ft_memdel(&tmp);
	}
}
