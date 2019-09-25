/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_stdin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/16 13:45:10 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/24 14:21:45 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	shell_stdin_to_line(t_vshdata *data)
{
	char	buffer[SHELL_BUF + 1];
	int		ret;

	ret = 1;
	data->line->line = ft_strdup("");
	if (data->line->line == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	while (ret > 0)
	{
		ret = read(STDIN_FILENO, buffer, SHELL_BUF);
		buffer[ret] = '\0';
		if (ret == -1)
			return (err_ret_exit(E_READ_STDIN_STR, EXIT_FAILURE));
		data->line->line = ft_strjoinfree_s1(data->line->line, buffer);
		if (data->line->line == NULL)
			return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	}
	return (FUNCT_SUCCESS);
}

/*
**	shell_stdin gets called when argc == 1 and vsh is not a shell
**	shell_stdin_to_line will read from stdin into line
**	shell_line_splitter will split the line into cmd lines
**	shell_lines_exec will execute each line until end or
**	until syntac error
*/

void		shell_stdin(t_vshdata *data)
{
	char	**lines;

	if (shell_stdin_to_line(data) != FUNCT_SUCCESS)
		return ;
	lines = shell_line_splitter(data);
	if (lines == NULL)
		return ;
	shell_lines_exec(data, lines);
	ft_strarrdel(&lines);
}
