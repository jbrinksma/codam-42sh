/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jornfuckup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:44:50 by omulder        #+#    #+#                */
/*   Updated: 2019/04/18 16:45:00 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		term_reset(t_term *term_p)
{
	int	ret;

	/* Is TCSANOW flag correct? */
	ret = tcsetattr(STDIN_FILENO, TCSANOW, term_p->old_termios_p);
	if (ret == -1)
		return (FUNCT_SUCCESS);
	return (FUNCT_SUCCESS);
}

void	term_free_termp(t_term *term_p)
{
	if (term_p)
	{
		if (term_p->old_termios_p)
			free(term_p->old_termios_p);
		if (term_p->termios_p)
			free(term_p->termios_p);
		free(term_p);
	}
}

int		shell_start(void)
{
	int		status;
	char	*line;
	char	***cmd_tab;

	status = 1;
	line = NULL;
	cmd_tab = NULL;
	while (status != CTRLD)
	{
		shell_display_prompt();
		status = input_read(&line);
		// if (status != CTRLD)
		// 	status = parser_lexer(&cmd_tab, line);
		ft_strdel(&line);
		ft_putendl("");
	}
	return (FUNCT_SUCCESS);
}
