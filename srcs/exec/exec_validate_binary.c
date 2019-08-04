/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_validate_binary.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/03 17:21:53 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/04 13:17:05 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		exec_validate_binary(char *binary)
{
	char	dir_status;

	if (access(binary, F_OK) == -1)
	{
		ft_eprintf("vsh: no such file or directory: %s\n", binary);
		return (err_ret_exit(NULL, EXIT_NOTFOUND));
	}
	if (access(binary, X_OK) == -1)
	{
		ft_eprintf("vsh: %s: Permission denied\n", binary);
		return (err_ret_exit(NULL, EXIT_NOT_EXECUTABLE));
	}
	dir_status = ft_isdir(binary);
	if (dir_status == -1)
	{
		ft_eprintf("vsh: could not get stat info of %s\n", binary);
		return (err_ret_exit(NULL, EXIT_NOT_EXECUTABLE));
	}
	else if (dir_status == true)
	{
		ft_eprintf("vsh: %s: Is a directory\n", binary);
		return (err_ret_exit(NULL, EXIT_NOT_EXECUTABLE));
	}
	return (FUNCT_SUCCESS);
}
