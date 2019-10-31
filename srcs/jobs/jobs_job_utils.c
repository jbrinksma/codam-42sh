/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_job_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 10:47:19 by tde-jong       #+#    #+#                */
/*   Updated: 2019/10/31 13:40:15 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

t_job	*jobs_find_current_job(t_job *joblist)
{
	t_job *job;
	t_job *toreturn;

	job = joblist;
	toreturn = job;
	while (job != NULL)
	{
		if (job->current > toreturn->current)
			toreturn = job;
		job = job->next;
	}
	return (toreturn);
}
