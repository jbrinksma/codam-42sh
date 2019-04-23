/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_parser_split_commands.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/22 16:05:52 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/23 16:24:55 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	IMPORTANT: After the parser_lexer has been added with an escape character
**	remover (for the escaped but unquoted ';' characters), these tests have to
**	be changed accordingly. (2019/04/23 13:37). (lol l33t).
*/

static int	return_test(char **commands, int ret)
{
	ft_freearray(&commands);
	return (ret);
}

static int	test_parser_split_commands_3(void)
{
	char	*str;
	char	**commands;

	str = ft_strdup("123;456\\\\\\;123;456;");
	parser_lexer(str, &commands);
	ft_strdel(&str);
	if (commands == NULL)
		return (FUNCT_FAILURE);
	if (commands[0] == NULL)
		return (return_test(commands, FUNCT_FAILURE));
	if (ft_strcmp(commands[0], "123"))
		return (return_test(commands, FUNCT_FAILURE));
	if (commands[0] == NULL)
		return (return_test(commands, FUNCT_FAILURE));
	if (ft_strcmp(commands[1], "456\\\\\\;123"))
		return (return_test(commands, FUNCT_FAILURE));
	if (commands[0] == NULL)
		return (return_test(commands, FUNCT_FAILURE));
	if (ft_strcmp(commands[2], "456"))
		return (return_test(commands, FUNCT_FAILURE));
	if (commands[0] == NULL)
		return (return_test(commands, FUNCT_FAILURE));
	if (ft_strcmp(commands[3], ""))
		return (return_test(commands, FUNCT_FAILURE));
	return (return_test(commands, FUNCT_SUCCESS));
}

static int	test_parser_split_commands_2(void)
{
	char	*str;
	char	**commands;

	str = ft_strdup("lalalaffffdsdg;asdgasdgas\\;dg as; dga sgas \\\";@");
	parser_lexer(str, &commands);
	ft_strdel(&str);
	if (commands == NULL)
		return (FUNCT_FAILURE);
	if (commands[0] == NULL)
		return (return_test(commands, FUNCT_FAILURE));
	if (ft_strcmp(commands[0], "lalalaffffdsdg"))
		return (return_test(commands, FUNCT_FAILURE));
	if (commands[0] == NULL)
		return (return_test(commands, FUNCT_FAILURE));
	if (ft_strcmp(commands[1], "asdgasdgas\\;dg as"))
		return (return_test(commands, FUNCT_FAILURE));
	if (commands[0] == NULL)
		return (return_test(commands, FUNCT_FAILURE));
	if (ft_strcmp(commands[2], " dga sgas \\\""))
		return (return_test(commands, FUNCT_FAILURE));
	if (commands[0] == NULL)
		return (return_test(commands, FUNCT_FAILURE));
	if (ft_strcmp(commands[3], "@"))
		return (return_test(commands, FUNCT_FAILURE));
	return (return_test(commands, FUNCT_SUCCESS));
}

static int	test_parser_split_commands_1(void)
{
	char	*str;
	char	**commands;

	str = ft_strdup("\"\";1'22'3'4';'1;';");
	parser_lexer(str, &commands);
	ft_strdel(&str);
	if (commands == NULL)
		return (FUNCT_FAILURE);
	if (commands[0] == NULL)
		return (return_test(commands, FUNCT_FAILURE));
	if (ft_strcmp(commands[0], ""))
		return (return_test(commands, FUNCT_FAILURE));
	if (commands[0] == NULL)
		return (return_test(commands, FUNCT_FAILURE));
	if (ft_strcmp(commands[1], "12234"))
		return (return_test(commands, FUNCT_FAILURE));
	if (commands[0] == NULL)
		return (return_test(commands, FUNCT_FAILURE));
	if (ft_strcmp(commands[2], "1;"))
		return (return_test(commands, FUNCT_FAILURE));
	if (commands[0] == NULL)
		return (return_test(commands, FUNCT_FAILURE));
	if (ft_strcmp(commands[3], ""))
		return (return_test(commands, FUNCT_FAILURE));
	return (return_test(commands, FUNCT_SUCCESS));
}

int			test_parser_split_commands(void)
{
	if (test_parser_split_commands_1() == FUNCT_FAILURE)
		return (FUNCT_FAILURE);
	if (test_parser_split_commands_2() == FUNCT_FAILURE)
		return (FUNCT_FAILURE);
	if (test_parser_split_commands_3() == FUNCT_FAILURE)
		return (FUNCT_FAILURE);
	return (FUNCT_SUCCESS);
}
