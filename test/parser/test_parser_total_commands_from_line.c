/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_parser_total_commands_from_line.c             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/23 16:22:12 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/23 19:03:44 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	return_test(char *line, int ret)
{
	if (line)
		ft_strdel(&line);
	return (ret);
}

static int	test_parser_total_commands_from_line_1(void)
{
	char	*line;
	int		result;

	line = ft_strdup("simple;command;line");
	if (line == NULL)
		return (return_test(NULL, E_ALLOC));
	result = parser_total_commands_from_line(line);
	if (result != 3)
		return (return_test(line, FUNCT_FAILURE));
	return (return_test(line, FUNCT_SUCCESS));
	ft_strdel(&line);
	line = ft_strdup("a;lot;of;commands;though;which;might;be;too;many;?");
	if (line == NULL)
		return (return_test(NULL, E_ALLOC));
	result = parser_total_commands_from_line(line);
	if (result != 11)
		return (return_test(line, FUNCT_FAILURE));
	ft_strdel(&line);
	line = ft_strdup("");
	if (line == NULL)
		return (return_test(NULL, E_ALLOC));
	result = parser_total_commands_from_line(line);
	if (result != 1)
		return (return_test(line, FUNCT_FAILURE));
	return (return_test(line, FUNCT_SUCCESS));
}

static int	test_parser_total_commands_from_line_2(void)
{
	char	*line;
	int		result;

	line = ft_strdup("commandline;with;escaped\\;semi;colon");
	if (line == NULL)
		return (return_test(NULL, E_ALLOC));
	result = parser_total_commands_from_line(line);
	if (result != 4)
		return (return_test(line, FUNCT_FAILURE));
	return (return_test(line, FUNCT_SUCCESS));
	ft_strdel(&line);
	line = ft_strdup("command\\;line\\;with;more\\;escaped;semi\\;colons");
	if (line == NULL)
		return (return_test(NULL, E_ALLOC));
	result = parser_total_commands_from_line(line);
	if (result != 3)
		return (return_test(line, FUNCT_FAILURE));
	return (return_test(line, FUNCT_SUCCESS));
}

static int	test_parser_total_commands_from_line_3(void)
{
	char	*line;
	int		result;

	line = ft_strdup("commandline;with\";quoted;\"semi;colons");
	if (line == NULL)
		return (return_test(NULL, E_ALLOC));
	result = parser_total_commands_from_line(line);
	if (result != 3)
		return (return_test(line, FUNCT_FAILURE));
	return (return_test(line, FUNCT_SUCCESS));
	ft_strdel(&line);
	line = ft_strdup("\"nice;weird;\";quoted\"semi;colons\"");
	if (line == NULL)
		return (return_test(NULL, E_ALLOC));
	result = parser_total_commands_from_line(line);
	if (result != 4)
		return (return_test(line, FUNCT_FAILURE));
	return (return_test(line, FUNCT_SUCCESS));
}

int			test_parser_total_commands_from_line(void)
{
	int ret;

	ret = test_parser_total_commands_from_line_1();
	if (ret != FUNCT_SUCCESS)
		return (ret);
	ret = test_parser_total_commands_from_line_2();
	if (ret != FUNCT_SUCCESS)
		return (ret);
	ret = test_parser_total_commands_from_line_3();
	return (ret);
}
