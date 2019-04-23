/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_parser_strdup_command_from_line.c             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/23 14:52:01 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/23 19:03:08 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	return_test(char *line, char *result, int ret)
{
	if (line)
		ft_strdel(&line);
	if (result)
		ft_strdel(&result);
	return (ret);
}

static int	test_parser_strdup_command_from_line_1(void)
{
	char	*line;
	char	*result;
	int		index;

	line = ft_strdup("simple;command;line");
	if (line == NULL)
		return (return_test(NULL, NULL, E_ALLOC));
	index = 0;
	result = parser_strdup_command_from_line(line, &index);
	if (result == 0)
		return (return_test(line, NULL, E_ALLOC));
	if (ft_strcmp(result, "simple") != 0)
		return (return_test(line, result, FUNCT_FAILURE));
	return (return_test(line, result, FUNCT_SUCCESS));
}

static int	test_parser_strdup_command_from_line_2(void)
{
	char	*line;
	char	*result;
	int		index;

	line = ft_strdup("more\\;complicated;line");
	if (line == NULL)
		return (return_test(NULL, NULL, E_ALLOC));
	index = 0;
	result = parser_strdup_command_from_line(line, &index);
	if (result == 0)
		return (return_test(line, NULL, E_ALLOC));
	if (ft_strcmp(result, "more\\;complicated") != 0)
		return (return_test(line, result, FUNCT_FAILURE));
	return (return_test(line, result, FUNCT_SUCCESS));
}

static int	test_parser_strdup_command_from_line_3(void)
{
	char	*line;
	char	*result;
	int		index;

	line = ft_strdup("\"quoted;command;line\"");
	if (line == NULL)
		return (return_test(NULL, NULL, E_ALLOC));
	index = 0;
	result = parser_strdup_command_from_line(line, &index);
	if (result == 0)
		return (return_test(line, NULL, E_ALLOC));
	if (ft_strcmp(result, "quoted;command;line") != 0)
		return (return_test(line, result, FUNCT_FAILURE));
	return (return_test(line, result, FUNCT_SUCCESS));
}

int			test_parser_strdup_command_from_line(void)
{
	int ret;

	ret = test_parser_strdup_command_from_line_1();
	if (ret != FUNCT_SUCCESS)
		return (ret);
	ret = test_parser_strdup_command_from_line_2();
	if (ret != FUNCT_SUCCESS)
		return (ret);
	ret = test_parser_strdup_command_from_line_3();
	return (ret);
}
