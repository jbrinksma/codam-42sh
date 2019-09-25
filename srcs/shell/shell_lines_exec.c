/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_lines_exec.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/19 19:50:33 by mavan-he       #+#    #+#                */
/*   Updated: 2019/09/22 16:52:37 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	shell_lines_exec(t_vshdata *data, char **lines)
{
	int i;

	i = 0;
	while (lines[i] != NULL)
	{
		if (shell_one_line(data, lines[i]) == FUNCT_ERROR)
			return ;
		i++;
	}
}
