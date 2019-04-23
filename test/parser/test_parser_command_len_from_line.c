/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_parser_command_len_from_line.c                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/23 15:29:24 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/23 19:02:03 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	return_test(char *line, int ret)
{
	if (line)
		ft_strdel(&line);
	return (ret);
}

static int	test_parser_command_len_from_line_1(void)
{
	char	*line;
	int		result;
	int		index;

	index = 0;
	line = ft_strdup("123456789");
	if (line == NULL)
		return (return_test(NULL, E_ALLOC));
	result = parser_command_len_from_line(line, &index);
	if (result != 9)
		return (return_test(line, FUNCT_FAILURE));
	return (return_test(line, FUNCT_SUCCESS));
	ft_strdel(&line);
	line = ft_strdup("1;2");
	if (line == NULL)
		return (return_test(NULL, E_ALLOC));
	result = parser_command_len_from_line(line, &index);
	if (result != 1)
		return (return_test(line, FUNCT_FAILURE));
	return (return_test(line, FUNCT_SUCCESS));
}

static int	test_parser_command_len_from_line_2(void)
{
	char	*line;
	int		result;
	int		index;

	index = 0;
	line = ft_strdup("123456\\;9");
	if (line == NULL)
		return (return_test(NULL, E_ALLOC));
	result = parser_command_len_from_line(line, &index);
	if (result != 9)
		return (return_test(line, FUNCT_FAILURE));
	return (return_test(line, FUNCT_SUCCESS));
	ft_strdel(&line);
	line = ft_strdup("1\\;\\;67");
	if (line == NULL)
		return (return_test(NULL, E_ALLOC));
	result = parser_command_len_from_line(line, &index);
	if (result != 7)
		return (return_test(line, FUNCT_FAILURE));
	return (return_test(line, FUNCT_SUCCESS));
}

static int	test_parser_command_len_from_line_3(void)
{
	char	*line;
	int		result;
	int		index;

	index = 0;
	line = ft_strdup("123\"5;7\"");
	if (line == NULL)
		return (return_test(NULL, E_ALLOC));
	result = parser_command_len_from_line(line, &index);
	if (result != 6)
		return (return_test(line, FUNCT_FAILURE));
	return (return_test(line, FUNCT_SUCCESS));
	ft_strdel(&line);
	line = ft_strdup("\"2\"\\;;aaa");
	if (line == NULL)
		return (return_test(NULL, E_ALLOC));
	result = parser_command_len_from_line(line, &index);
	if (result != 3)
		return (return_test(line, FUNCT_FAILURE));
	return (return_test(line, FUNCT_SUCCESS));
}

int			test_parser_command_len_from_line(void)
{
	int ret;

	ret = test_parser_command_len_from_line_1();
	if (ret != FUNCT_SUCCESS)
		return (ret);
	ret = test_parser_command_len_from_line_2();
	if (ret != FUNCT_SUCCESS)
		return (ret);
	ret = test_parser_command_len_from_line_3();
	return (ret);
}
