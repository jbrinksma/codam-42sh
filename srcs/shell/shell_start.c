/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_start.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:44:50 by omulder        #+#    #+#                */
/*   Updated: 2019/04/23 19:36:04 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		shell_start(void)
{
	int		status;
	char	*line;
	// char	***cmd_tab;

	status = 1;
	line = NULL;
	// cmd_tab = NULL;
	while (status != CTRLD)
	{
		shell_display_prompt();
		status = input_read(&line);
		// if (status != CTRLD)
		// 	status = parser(&cmd_tab, line);ß
		ft_strdel(&line);
		ft_putendl("");
	}
	return (FUNCT_SUCCESS);
}
