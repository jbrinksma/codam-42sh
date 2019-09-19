/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_get_pid_state.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/16 10:04:00 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/09/16 16:38:31 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <sys/wait.h>

int		tools_get_pid_state(pid_t pid)
{
	int		status;
	pid_t	result;

	result = waitpid(pid, &status, WNOHANG);
	if (WIFSTOPPED(status))
		return (PID_STATE_SUSPEND);
	if (WIFCONTINUED(status))
		return (PID_STATE_RUNNING);
	if (result != 0)
		return (PID_STATE_EXIT);
	return (PID_STATE_RUNNING);
}
