/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/22 15:25:46 by rkuijper       #+#    #+#                */
/*   Updated: 2019/11/07 15:12:35 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int			jobs_update_job_command(t_job *job, t_proc *proc, char **av)
{
	int i;

	i = 0;
	while (av[i] != NULL)
	{
		if (i != 0)
			job->command = ft_strjoinchrfree(job->command, ' ', 1);
		job->command = ft_strjoinfree_s1(job->command, av[i]);
		i++;
	}
	if (proc->next != NULL)
			job->command = ft_strjoinfree_s1(job->command, " | ");
	return (FUNCT_SUCCESS);
}
