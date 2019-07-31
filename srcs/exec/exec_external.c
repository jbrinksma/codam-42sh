/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_external.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-jong <tde-jong@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 10:47:19 by tde-jong       #+#    #+#                */
/*   Updated: 2019/07/30 18:42:00 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>
#include <sys/wait.h>
#include <termios.h>
#include <signal.h>

static void		term_flags_init(void)
{
	g_state->termios_p->c_lflag |= ICANON;
	g_state->termios_p->c_lflag |= ECHO;
	g_state->termios_p->c_lflag |= ISIG;
	tcsetattr(STDIN_FILENO, TCSANOW, g_state->termios_p);
}

static void		term_flags_destroy(void)
{
	g_state->termios_p->c_lflag &= ~ICANON;
	g_state->termios_p->c_lflag &= ~ECHO;
	g_state->termios_p->c_lflag &= ~ISIG;
	tcsetattr(STDIN_FILENO, TCSANOW, g_state->termios_p);
}

void			signal_print_newline(int signum)
{
	(void)signum;
	ft_putchar('\n');
}

static bool	exec_bin(char *binary, char **args, char **vshenviron)
{
	pid_t	pid;
	int		status;

	term_flags_init();
	pid = fork();
	if (pid < 0)
		return (false);
	if (pid > 0)
		signal(SIGINT, signal_print_newline);
	else
		execve(binary, args, vshenviron);
	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_state->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_state->exit_code = EXIT_FATAL + WTERMSIG(status);
	signal(SIGINT, SIG_DFL);
	term_flags_destroy();
	free(vshenviron);
	return (true);
}

bool			exec_external(char **args, t_vshdata *vshdata)
{
	char	**vshenviron;
	char	*binary;

	binary = ft_strdup(args[0]);
	if (binary == NULL)
		return (false);
	if (args[0][0] != '/' && ft_strnequ(args[0], "./", 2) == 0 &&
		ft_strnequ(args[0], "../", 3) == 0)
	{
		ft_strdel(&binary);
		binary = exec_find_binary(args[0], vshdata);
		if (binary == NULL)
			return (false);
	}
	vshenviron = env_lsttoarr(vshdata->envlst, ENV_EXTERN);
	if (vshenviron == NULL)
	{
		ft_printf("vsh: failed to allocate enough memory!\n");
		g_state->exit_code = EXIT_FAILURE;
		return (false);
	}
	return (exec_bin(binary, args, vshenviron));
}
