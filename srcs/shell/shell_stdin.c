/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_stdin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/16 13:45:10 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/16 16:34:34 by mavan-he      ########   odam.nl         */
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
	data->line->line = ft_strjoinfree_s1(data->line->line, "\n");
	if (data->line->line == NULL)
		return (err_ret_exit(E_ALLOC_STR, EXIT_FAILURE));
	return (FUNCT_SUCCESS);
}

void		shell_stdin(t_vshdata *data)
{
	if (shell_stdin_to_line(data) != FUNCT_SUCCESS)
		return ;
	shell_one_line(data);
}
