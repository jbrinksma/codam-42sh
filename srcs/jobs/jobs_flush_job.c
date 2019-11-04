/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_flush_job.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 10:59:38 by rkuijper       #+#    #+#                */
/*   Updated: 2019/11/04 11:53:27 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void			jobs_flush_job(t_job *job)
{
	jobs_flush_process(job->processes);
	if (job->command != NULL)
		ft_strdel(&job->command);
	ft_memdel((void**)&job);
}
