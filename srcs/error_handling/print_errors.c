/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_errors.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/22 11:14:25 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/05 15:30:53 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>

int		error_return(int ret, int error, char *opt_str)
{
	if (error == E_BADFD)
		ft_eprintf("vsh: %s: bad file descriptor\n", opt_str);
	else if (error == E_DUP)
		ft_eprintf("vsh: failed to duplicate file descriptor\n");
	else if (error == E_OPEN)
		ft_eprintf("vsh: no perm / no such file or directory\n");
	else if (error == E_BADRED)
		ft_eprintf("vsh: %s: bad redirect\n", opt_str);
	else if (error == E_CLOSE)
		ft_eprintf("vsh: failed to close file descriptor\n");
	else if (error == E_ALLOC)
		ft_eprintf("vsh: failed to allocate enough memory\n");
	g_state->exit_code = EXIT_FAILURE;
	return (ret);
}

int		err_ret_exit(char *str, int exitcode)
{
	g_state->exit_code = exitcode;
	if (str != NULL)
		ft_eprintf("%s", str);
	return (FUNCT_ERROR);
}

void	err_void_exit(char *str, int exitcode)
{
	g_state->exit_code = exitcode;
	if (str != NULL)
		ft_eprintf("%s", str);
}

int		err_ret(char *str)
{
	if (str != NULL)
		ft_eprintf("%s", str);
	return (FUNCT_ERROR);
}
