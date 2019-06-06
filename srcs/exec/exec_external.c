/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_external.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-jong <tde-jong@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 10:47:19 by tde-jong       #+#    #+#                */
/*   Updated: 2019/06/06 10:46:47 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include "unistd.h"
#include <sys/wait.h>

static bool	exec_bin(char **args, char **env, int *exit_code)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (false);
	if (pid == 0)
		execve(args[0], args, env);
	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		*exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*exit_code = EXIT_FATAL + WTERMSIG(status);
	return (true);
}

bool		exec_external(char **args, char ***env, int *exit_code)
{
	char *binary;

	if (args[0][0] != '/' && !ft_strnequ(args[0], "./", 2))
	{
		binary = exec_find_binary(args[0], *env);
		if (binary == NULL)
			return (false);
		free(args[0]);
		args[0] = binary;
	}
	return (exec_bin(args, *env, exit_code));
}
