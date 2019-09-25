/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_external.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 10:47:19 by tde-jong       #+#    #+#                */
/*   Updated: 2019/09/24 16:12:09 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>
#include <sys/wait.h>
#include <termios.h>
#include <signal.h>

static void		term_flags_init(t_termios *termios_p)
{
	if (g_state->shell_type == SHELL_NON_INTERACT)
		return ;
	termios_p->c_lflag |= (ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSANOW, termios_p);
}

static void		term_flags_destroy(t_termios *termios_p)
{
	if (g_state->shell_type == SHELL_NON_INTERACT)
		return ;
	termios_p->c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSANOW, termios_p);
}

static void		exec_bin_handlewait(pid_t pid)
{
	int		status;

	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_state->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_state->exit_code = EXIT_FATAL + WTERMSIG(status);
}

static void		exec_bin(char *binary, char **args, char **vshenviron,
t_vshdata *data)
{
	pid_t	pid;

	if (exec_validate_binary(binary) == FUNCT_ERROR)
		return ;
	if (data->term->termios_p != NULL)
		term_flags_init(data->term->termios_p);
	pid = fork();
	if (pid < 0)
		return (err_void_exit(E_FORK_STR, EXIT_FAILURE));
	if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		if (data->exec_flags & EXEC_ISPIPED)
			exec_add_pid_to_pipeseqlist(data, pid);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		execve(binary, args, vshenviron);
		ft_eprintf(E_FAIL_EXEC_P, binary);
		exit(EXIT_FAILURE);
	}
	if (data->exec_flags & EXEC_WAIT)
		exec_bin_handlewait(pid);
	term_flags_destroy(data->term->termios_p);
}

void			exec_external(char **args, t_vshdata *data)
{
	char	**vshenviron;
	char	*binary;

	binary = ft_strdup(args[0]);
	vshenviron = env_lsttoarr(data->envlst);
	if (binary == NULL || vshenviron == NULL)
	{
		ft_strdel(&binary);
		free(vshenviron);
		ft_eprintf(E_ALLOC_STR);
		g_state->exit_code = EXIT_FAILURE;
		return ;
	}
	if (args[0][0] != '/' && ft_strnequ(args[0], "./", 2) == 0 &&
		ft_strnequ(args[0], "../", 3) == 0)
	{
		ft_strdel(&binary);
		if (exec_find_binary(args[0], data, &binary) == FUNCT_SUCCESS)
			exec_bin(binary, args, vshenviron, data);
	}
	else
		exec_bin(binary, args, vshenviron, data);
	free(vshenviron);
	ft_strdel(&binary);
}
