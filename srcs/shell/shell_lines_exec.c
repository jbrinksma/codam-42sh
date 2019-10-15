/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_lines_exec.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/19 19:50:33 by mavan-he       #+#    #+#                */
/*   Updated: 2019/10/01 12:30:56 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	shell_lines_exec(t_vshdata *data, char **lines)
{
	int i;

	i = 0;
	while (lines[i] != NULL)
	{
		if (data->fc_flags & FC_PRINT_CMD)
			ft_printf("%s\n", lines[i]);
		if (shell_one_line(data, lines[i]) == FUNCT_ERROR)
			return ;
		i++;
	}
}
