/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_start.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:44:50 by omulder        #+#    #+#                */
/*   Updated: 2019/05/05 12:27:43 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		shell_start(void)
{
	int			status;
	char		*line;
	t_list		*cmd_tab;

	status = 1;
	line = NULL;
	cmd_tab = NULL;
	while (status != CTRLD)
	{
		shell_display_prompt();
		status = input_read(&line);
		parser_lexer(line, &cmd_tab);
		ft_strdel(&line);
		cmd_tab = NULL;
		ft_putendl("");
	}
	return (FUNCT_SUCCESS);
}
