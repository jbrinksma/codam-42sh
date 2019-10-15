/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/15 14:41:31 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/01 12:03:45 by omulder       ########   odam.nl         */
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

/*
**	shell_args gets called when argc > 1
**	shell_check_file will check if arg 1 is a valid file
**	shell_init_line will read the input from file into line
**	shell_line_splitter will split the line into cmd lines
**	shell_lines_exec will execute each line until end or
**	until syntac error
*/

void		shell_args(t_vshdata *data, char *filepath)
{
	char	**lines;
	char	*path;

	if (shell_get_path(data, filepath, &path) == FUNCT_ERROR)
		return ;
	if (shell_check_file(path) != FUNCT_SUCCESS)
		return ;
	if (shell_init_line(data, path) == FUNCT_ERROR)
		return ;
	ft_strdel(&path);
	lines = shell_line_splitter(data);
	if (lines == NULL)
		return ;
	shell_lines_exec(data, lines);
	ft_strarrdel(&lines);
}
