/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 20:29:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/16 20:23:02 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		reset_term(t_term *term_p)
{
	int	ret;

	/* Is TCSANOW flag correct? */
	ret = tcsetattr(STDIN_FILENO, TCSANOW, term_p->old_termios_p);
	if (ret == -1)
		return (FUNCT_SUCCESS);
	return (FUNCT_SUCCESS);
}

void	free_term_p(t_term *term_p)
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

int		read_input(t_term *term_p)
{
	char	*buf;
	char	*line;
	int		cr;

	(void)term_p;
	cr = 0;
	buf = ft_strnew(3);
	line = ft_strnew(0);
	while (!cr)
	{
		ft_bzero(buf, 3);
		read(STDIN_FILENO, buf, 3);
		ft_printf("%s\n", buf);
		line = ft_strjoinfree(line, buf, 1);
		cr = 1;
	}
	return (FUNCT_SUCCESS);
}

int		start_shell(t_term *term_p)
{
	int		status;

	status = 1;
	while (status != -1)
	{
		display_prompt();
		read_input(term_p);
		status = -1;
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
	term_p = init_term();
	/* if !term_p: send appropriate error message/log */
	if (!term_p)
		return (EXIT_FAILURE);
	start_shell(term_p);
	reset_term(term_p);
}
