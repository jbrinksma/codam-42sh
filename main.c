/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 20:29:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/16 21:46:19 by jbrinksm      ########   odam.nl         */
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

void	input_echo(char *buf)
{
	if (buf[1] == '\0' && buf[2] == '\0')
	{
		if (ft_isprint(buf[0]))
			ft_putchar(buf[0]);
		else if (buf[0] == 4)
			ft_putstr("^D");
	}
}

int		input_read(t_term *term_p)
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
		/* carriage return is still translated into newline */
		if (ft_strcmp(buf, "\n"))
		{
			input_echo(buf);
			line = ft_strjoinfree(line, buf, 1);
		}
		else
			cr = 1;
	}
	return (FUNCT_SUCCESS);
}

int		shell_start(t_term *term_p)
{
	int		status;

	status = 1;
	while (status != -1)
	{
		shell_display_prompt();
		input_read(term_p);
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
	term_p = term_init();
	/* if !term_p: send appropriate error message/log */
	if (!term_p)
		return (EXIT_FAILURE);
	shell_start(term_p);
	term_reset(term_p);
}
