/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_validate_binary.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/03 17:21:53 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/22 11:32:10 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		exec_validate_binary(char *binary)
{
	char	dir_status;

	if (access(binary, F_OK) == -1)
	{
		ft_eprintf(E_NO_SUCH_P, binary);
		return (err_ret_exit(NULL, EXIT_NOTFOUND));
	}
	if (access(binary, X_OK) == -1)
	{
		ft_eprintf(E_N_PER_DEN, binary);
		return (err_ret_exit(NULL, EXIT_NOT_EXECUTABLE));
	}
	dir_status = ft_isdir(binary);
	if (dir_status == -1)
	{
		ft_eprintf(E_STAT_P, binary);
		return (err_ret_exit(NULL, EXIT_NOT_EXECUTABLE));
	}
	else if (dir_status == true)
	{
		ft_eprintf(E_P_IS_DIR, binary);
		return (err_ret_exit(NULL, EXIT_NOT_EXECUTABLE));
	}
	return (FUNCT_SUCCESS);
}
