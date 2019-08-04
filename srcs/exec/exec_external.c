/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_external.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 10:47:19 by tde-jong       #+#    #+#                */
/*   Updated: 2019/08/04 16:26:06 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>
#include <sys/wait.h>
#include <termios.h>
#include <signal.h>

static void		term_flags_init(void)
{
	g_state->termios_p->c_lflag |= (ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSANOW, g_state->termios_p);
}

static void		term_flags_destroy(void)
{
	g_state->termios_p->c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSANOW, g_state->termios_p);
}

void			signal_print_newline(int signum)
{
	(void)signum;
	ft_putchar('\n');
}

static void		exec_bin(char *binary, char **args, char **vshenviron)
{
	pid_t	pid;
	int		status;

	if (exec_validate_binary(binary) == FUNCT_ERROR)
		return ;
	term_flags_init();
	pid = fork();
	if (pid < 0)
		return (err_void_exit(E_FORK_STR, EXIT_FAILURE));
	if (pid > 0)
		signal(SIGINT, signal_print_newline);
	else
	{
		execve(binary, args, vshenviron);
		ft_eprintf("vsh: failed to execute %s\n", binary);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_state->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_state->exit_code = EXIT_FATAL + WTERMSIG(status);
	signal(SIGINT, SIG_DFL);
	term_flags_destroy();
}

void			exec_external(char **args, t_vshdata *vshdata)
{
	char	**vshenviron;
	char	*binary;

	binary = ft_strdup(args[0]);
	vshenviron = env_lsttoarr(vshdata->envlst, ENV_EXTERN);
	if (binary == NULL || vshenviron == NULL)
	{
		ft_strdel(&binary);
		free(vshenviron);
		ft_eprintf("vsh: failed to allocate enough memory!\n");
		g_state->exit_code = EXIT_FAILURE;
		return ;
	}
	if (args[0][0] != '/' && ft_strnequ(args[0], "./", 2) == 0 &&
		ft_strnequ(args[0], "../", 3) == 0)
	{
		ft_strdel(&binary);
		if (exec_find_binary(args[0], vshdata, &binary) == FUNCT_SUCCESS)
			exec_bin(binary, args, vshenviron);
	}
	else
		exec_bin(binary, args, vshenviron);
	free(vshenviron);
	ft_strdel(&binary);
}
