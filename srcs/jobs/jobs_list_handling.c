/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_list_handling.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 10:47:19 by tde-jong       #+#    #+#                */
/*   Updated: 2019/11/07 15:02:15 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

t_job			*jobs_new_job(void)
{
	t_job *new;

	new = (t_job*)ft_memalloc(sizeof(t_job));
	if (new == NULL)
		return (NULL);
	new->bg = false;
	new->command = ft_strnew(1);
	return (new);
}

t_job			*jobs_remove_job(t_job **joblist, pid_t pgid)
{
	t_job	*job;
	t_job	*tmp;

	if (joblist == NULL || *joblist == NULL)
		return (NULL);
	job = *joblist;
	if (job->pgid == pgid)
	{
		*joblist = job->next;
		job->next = NULL;
		return (job);
	}
	while (job != NULL && job->next != NULL)
	{
		if (job->next->pgid == pgid)
		{
			tmp = job->next;
			job->next = tmp->next;
			tmp->next = NULL;
			return (tmp);
		}
		job = job->next;
	}
	return (NULL);
}

static int		insert_job(t_vshdata *data, t_job *job, int *jid)
{
	t_job	*tmp;

	tmp = data->jobs->joblist;
	(*jid) = tmp->job_id + 1;
	while (tmp->next)
	{
		if (tmp->pgid == job->pgid)
			return (FUNCT_FAILURE);
		tmp = tmp->next;
		if (tmp->job_id > (*jid))
			(*jid) = tmp->job_id + 1;
		else
			(*jid)++;
	}
	if (tmp->pgid == job->pgid)
		return (FUNCT_FAILURE);
	tmp->next = job;
	return (FUNCT_SUCCESS);
}

t_job			*jobs_add_job(t_vshdata *data, t_job *job)
{
	int		jid;

	jid = 1;
	if (data->jobs->joblist == NULL)
		data->jobs->joblist = job;
	else
	{
		if (insert_job(data, job, &jid) == FUNCT_FAILURE)
			return (job);
	}
	job->job_id = jid;
	job->current = builtin_jobs_new_current_val(data->jobs->joblist);
	return (job);
}

t_job			*jobs_last_child(t_job *job)
{
	t_job *tmp;

	if (job == NULL)
		return (NULL);
	tmp = job;
	while (tmp->child)
		tmp = tmp->child;
	return (tmp);
}
