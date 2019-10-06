/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handle_child_death.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/16 09:51:07 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/06 12:31:18 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <signal.h>

/*
**	When a child process has died, we will check the pipeseqlist to see
**	if a child process has exited in the pipe sequence. If we find it, any
**	processes in the sequence that are running before it will be killed.
*/

void		signal_handle_child_death(int signum)
{
	t_pipeseqlist	*pipeseqprobe;
	bool			killmode;

	if (signum == SIGCHLD)
	{
		pipeseqprobe = g_data->pipeseq;
		killmode = false;
		while (pipeseqprobe != NULL)
		{
			if (killmode == true)
				kill(pipeseqprobe->pid, SIGINT);
			if (tools_get_pid_state(pipeseqprobe->pid) == PID_STATE_EXIT)
				killmode = true;
			pipeseqprobe = pipeseqprobe->next;
		}
		signal(SIGCHLD, signal_handle_child_death);
	}
}
