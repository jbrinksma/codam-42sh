/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/22 15:25:46 by rkuijper       #+#    #+#                */
/*   Updated: 2019/10/22 15:47:50 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int			jobs_update_job_command(t_job *job, char **av)
{
	int i;

	i = 0;
	if (g_data->exec_flags & EXEC_ISPIPED)
	{
		if (job->command[0] != '\0')
			job->command = ft_strjoinfree_s1(job->command, " | ");
	}
	while (av[i] != NULL)
	{
		if (i != 0)
			job->command = ft_strjoinchrfree(job->command, ' ', 1);
		job->command = ft_strjoinfree_s1(job->command, av[i]);
		i++;
	}
	return (FUNCT_SUCCESS);
}
