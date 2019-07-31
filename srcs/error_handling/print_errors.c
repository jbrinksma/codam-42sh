/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_errors.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/22 11:14:25 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/28 13:43:51 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>

int	error_return(int ret, int error, char *opt_str)
{
	if (error == E_BADFD)
		ft_eprintf("vsh: %s: bad file descriptor\n", opt_str);
	else if (error == E_DUP)
		ft_putstr_fd("vsh: failed to duplicate file descriptor\n",
		STDERR_FILENO);
	else if (error == E_OPEN)
		ft_putstr_fd("vsh: no perm / no such file or directory\n",
		STDERR_FILENO);
	else if (error == E_BADRED)
		ft_eprintf("vsh: %s: bad redirect\n", opt_str);
	else if (error == E_CLOSE)
		ft_putstr_fd("vsh: failed to close file descriptor\n",
		STDERR_FILENO);
	g_state->exit_code = EXIT_FAILURE;
	return (ret);
}
