/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 20:29:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/10/29 12:22:48 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <signal.h>

/*
**	This structure is used to save the exit code and shell type.
*/

static void	init_shell(void)
{
	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	if (g_state == NULL)
	{
		ft_eprintf(E_ALLOC_STR);
		exit(EXIT_FAILURE);
	}
	g_state->shell_type = SHELL_INTERACT;
	if (isatty(STDIN_FILENO))
	{
		g_state->pid = getpgrp();
		while (tcgetpgrp(STDIN_FILENO) != g_state->pid)
		{
			kill(-g_state->pid, SIGTTIN);
			g_state->pid = getpgrp();
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGCHLD, signal_handle_child_death);
		g_state->pid = getpid();
		setpgid(g_state->pid, g_state->pid);
		tcsetpgrp(STDIN_FILENO, g_state->pid);
	}
}

int			main(int argc, char **argv)
{
	t_vshdata	*data;

	init_shell();
	data = shell_init_vshdata();
	if (data == NULL)
		return (EXIT_FAILURE);
	if (argc > 1 || isatty(STDIN_FILENO) != 1)
	{
		g_state->shell_type = SHELL_NON_INTERACT;
		if (argc > 1)
			shell_args(data, argv[1]);
		else
			shell_stdin(data);
		return (g_state->exit_code);
	}
	if (shell_init_term(data) == FUNCT_ERROR)
		return (EXIT_FAILURE);
	shell_start(data);
	return (g_state->exit_code);
}
