/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/15 14:41:31 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/16 17:38:22 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	shell_check_file(char *filepath)
{
	int ret;

	if (access(filepath, F_OK) != 0)
	{
		ft_eprintf(E_NO_SUCH_P, filepath);
		return (err_ret_exit(NULL, EXIT_NOTFOUND));
	}
	if (access(filepath, R_OK) != 0)
	{
		ft_eprintf(E_N_PER_DEN, filepath);
		return (err_ret_exit(NULL, EXIT_NOT_EXECUTABLE));
	}
	ret = ft_is_regular_file(filepath);
	if (ret == FUNCT_ERROR)
	{
		ft_eprintf(E_STAT_P, filepath);
		return (err_ret_exit(NULL, EXIT_FAILURE));
	}
	return (ret);
}

void		shell_args(t_vshdata *data, char *filepath)
{
	if (shell_get_path(data, &filepath) == FUNCT_ERROR)
		return ;
	if (shell_check_file(filepath) != FUNCT_SUCCESS)
		return ;
	if (shell_init_line(data, filepath) == FUNCT_FAILURE)
		return ;
	ft_strdel(&filepath);
	shell_one_line(data);
	return ;
}
