/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_read.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/17 14:03:16 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/17 15:12:59 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		input_echo(char *buf)
{
	if (buf[0] != '\x1b')
	{
		if (buf[0] == 3)
			ft_printf("^C");
		else if (buf[0] == 4)
			return (CTRLD);
		else
			ft_printf("%s", buf);
	}
	else
	{
		if (!ft_strcmp(&buf[1], "[D"))
			ft_printf("<-");
		else if (!ft_strcmp(&buf[1], "[C"))
			ft_printf("->");
		else if (!ft_strcmp(&buf[1], "[A"))
			ft_printf("/\\");
		else if (!ft_strcmp(&buf[1], "[B"))
			ft_printf("\\/");

		else if (!ft_strcmp(&buf[1], "[1;2P"))
			ft_printf("prtscr");
		else if (!ft_strcmp(&buf[1], "[H"))
			ft_printf("home");
		else if (!ft_strcmp(&buf[1], "[3~"))
			ft_printf("delete");
		else if (!ft_strcmp(&buf[1], "[2~"))
			ft_printf("insert");
		else if (!ft_strcmp(&buf[1], "[F"))
			ft_printf("end");
		else if (!ft_strcmp(&buf[1], "[5~"))
			ft_printf("pageup");
		else if (!ft_strcmp(&buf[1], "[6~"))
			ft_printf("pagedown");

		else if (!ft_strcmp(&buf[1], "OP"))
			ft_printf("f1");
		else if (!ft_strcmp(&buf[1], "OQ"))
			ft_printf("f2");
		else if (!ft_strcmp(&buf[1], "OR"))
			ft_printf("f3");
		else if (!ft_strcmp(&buf[1], "OS"))
			ft_printf("f4");
		else if (!ft_strcmp(&buf[1], "[15~"))
			ft_printf("f5");
		else if (!ft_strcmp(&buf[1], "[17~"))
			ft_printf("f6");
		else if (!ft_strcmp(&buf[1], "[18~"))
			ft_printf("f7");
		else if (!ft_strcmp(&buf[1], "[19~"))
			ft_printf("f8");
		else if (!ft_strcmp(&buf[1], "[20~"))
			ft_printf("f9");
		else if (!ft_strcmp(&buf[1], "[21~"))
			ft_printf("f10");
		else if (!ft_strcmp(&buf[1], "[24~"))
			ft_printf("f12");

		else if (!buf[1])
			ft_printf("esc");
		else
			ft_printf("unknown char: >%s<", &buf[1]);
	}
	return (FUNCT_SUCCESS);
}

static int	return_input_read(char *buf, int returnvalue)
{
	ft_strdel(&buf);
	return (returnvalue);
}

int		input_read(char **line)
{
	char	*buf;
	int		status;

	buf = ft_strnew(11);
	*line = ft_strnew(0);
	status = FUNCT_SUCCESS;
	while (status == FUNCT_SUCCESS)
	{
		ft_bzero(buf, 11);
		read(STDIN_FILENO, buf, 10);
		if (ft_strcmp(buf, "\n"))
		{
			status = input_echo(buf);
			*line = ft_strjoinfree(*line, buf, 1);
		}
		else
			status = CR;
	}
	return (return_input_read(buf, status));
}
