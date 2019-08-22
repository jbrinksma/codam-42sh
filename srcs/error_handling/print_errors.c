/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_errors.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/22 11:14:25 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/22 11:19:59 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>

int		error_return(int ret, int error, char *opt_str)
{
	if (error == E_BADFD)
		ft_eprintf(E_P_BAD_FD, opt_str);
	else if (error == E_DUP)
		ft_eprintf(E_FAIL_DUP_FD);
	else if (error == E_OPEN)
		ft_eprintf(E_NO_PERM_NO_SUCH);
	else if (error == E_BADRED)
		ft_eprintf(E_P_BAD_REDIR, opt_str);
	else if (error == E_CLOSE)
		ft_eprintf(E_FD_CLOSE);
	else if (error == E_ALLOC)
		ft_eprintf(E_ALLOC_STR);
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
