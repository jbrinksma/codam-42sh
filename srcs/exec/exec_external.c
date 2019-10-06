/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_external.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 10:47:19 by tde-jong       #+#    #+#                */
/*   Updated: 2019/10/05 11:40:46 by jbrinksm      ########   odam.nl         */
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

	status = 0;
	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_state->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_state->exit_code = EXIT_FATAL + WTERMSIG(status);
}

/*
**	Check if `char *binary` is valid.
**	Set termios structure to default values.
**	Run cmd_word, and wait for it to finish if the EXEC_WAIT flag is set.
**	Set termios structure back to our special values.
*/

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

/*
**	Create the environment for the command about to be executed.
**	Use the cmd_word (see GRAMMAR) as binary name (+ optional relative path),
**	or if cmd_word contains one or more slashes ('/'), fetch the absolute path
**	from the PATH variable, and set `char *binary` equal to that instead.
**	Then: call `exec_bin`.
*/

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
	if (ft_strchr(args[0], '/') == NULL)
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
