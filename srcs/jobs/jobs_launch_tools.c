/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jobs_launch_tools.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 11:00:24 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/11/05 13:57:56 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	jobs_launch_setup_stds(t_proc *proc, int fds[3], int pipes[2])
{
	if (proc->next != NULL)
	{
		if (pipe(pipes) < 0)
		{
			ft_eprintf(E_NO_PIPE);
			exit(1);
		}
		fds[1] = pipes[1];
	}
	else
		fds[1] = STDOUT_FILENO;
}

void	jobs_launch_cleanup_after_proc(t_proc *proc, int fds[3], int pipes[2])
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
