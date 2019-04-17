/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 20:29:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/17 15:18:54 by jbrinksm      ########   odam.nl         */
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
		if (status != CTRLD)
			status = parser_lexer(&cmd_tab, line);
		ft_strdel(&line);
		ft_putendl("");
	}
	return (FUNCT_SUCCESS);
}

/*
**	ft_printf alloc error handling
*/

int		main(int argc, char **argv)
{
	t_term	*term_p;

	(void)argv;
	(void)argc;
	term_p = term_init();
	/* if !term_p: send appropriate error message/log */
	if (!term_p)
		return (EXIT_FAILURE);
	shell_start();
	term_reset(term_p);
	term_free_termp(term_p);
}
