/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unit_test.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:37:32 by omulder        #+#    #+#                */
/*   Updated: 2019/05/02 11:34:36 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	General note: We have to make sure that we redirect the STDOUT to some sort
**	of file, so that we don't destroy the test_suite output.
**	(Also, see the comments at builtin_echo.)
*/

#include "vsh.h"
#include <criterion/criterion.h>

TestSuite(term_is_valid);

Test(term_is_valid, basic)
{
	char *env1;
	char *env2;

	env1 = "TERM=non_valid_term";
	env2 = "TERM=vt100";
	cr_expect_eq(term_is_valid(&env1), FUNCT_FAILURE);
	cr_expect_eq(term_is_valid(&env2), FUNCT_SUCCESS);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(term_init_struct);

Test(term_init_struct, basic)
{
	t_term	*term_p;
	
	term_p = term_init_struct();
	cr_assert(term_p != NULL);
	cr_expect_neq(term_p->termios_p, NULL);
	cr_expect_neq(term_p->old_termios_p, NULL);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(term_free_struct);

Test(term_free_struct, basic)
{
	t_term	*term_p;

	term_p = term_init_struct();

	/* not sure how to have this as prerequisite as test any other way */
	cr_assert(term_p != NULL, "prerequisite failed: term_init_struct");

	term_free_struct(&term_p);
	cr_expect_eq(term_p, NULL);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(get_environ_cpy);

Test(get_environ_cpy, basic)
{
	extern char **environ;
	char		**vshenviron;
	int			index;
	
	vshenviron = get_environ_cpy();
	cr_assert(vshenviron != NULL);
	index = 0;
	while (vshenviron[index] != NULL && environ[index] != NULL)
	{
		cr_expect_str_eq(vshenviron[index], environ[index]);
		index++;
	}
	cr_expect_eq(environ[index], NULL);
	cr_expect_eq(vshenviron[index], NULL);
	
	/* Do I have to free? forked program should exit here */
	ft_freearray(&vshenviron);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(term_get_attributes);

Test(term_get_attributes, basic)
{
	t_term	*term_p;

	cr_expect_eq(term_get_attributes(STDIN_FILENO, NULL), FUNCT_FAILURE);
	term_p = term_init_struct();

	/* not sure how to have this as prerequisite as test any other way */
	cr_assert(term_p != NULL, "prerequisite failed: term_init_struct");

	// cr_expect_eq(term_get_attributes(STDIN_FILENO, term_p), FUNCT_SUCCESS);
	cr_expect_eq(term_get_attributes(STDOUT_FILENO, term_p), FUNCT_SUCCESS);
	cr_expect_eq(term_get_attributes(STDERR_FILENO, term_p), FUNCT_SUCCESS);
	cr_expect_eq(term_get_attributes(10101, term_p), FUNCT_FAILURE);
	
	/* Do I have to free? forked program should exit here */
	term_free_struct(&term_p);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(parser_split_line_to_commands);

Test(parser_split_line_to_commands, basic)
{
	char	**commands;

	commands = NULL;
	parser_lexer("\"\";1'22'3'4';'1;';", &commands);
	cr_assert(commands != NULL);
	cr_expect_str_eq(commands[0], "");
	cr_expect_str_eq(commands[1], "12234");
	cr_expect_str_eq(commands[2], "1;");
	cr_expect_str_eq(commands[3], "");

	/* Do I have to free? forked program should exit here */
	ft_freearray(&commands);
}

Test(parser_split_line_to_commands, escaped_command_seperator)
{
	char	**commands;

	commands = NULL;
	parser_lexer("lalalaffffdsdg;asdgasdgas\\;dg as; dga sgas \\\";@", &commands);
	cr_assert(commands != NULL);
	cr_expect_str_eq(commands[0], "lalalaffffdsdg");
	cr_expect_str_eq(commands[1], "asdgasdgas\\;dg as");
	cr_expect_str_eq(commands[2], " dga sgas \\\"");
	cr_expect_str_eq(commands[3], "@");

	/* Do I have to free? forked program should exit here */
	ft_freearray(&commands);
}

Test(parser_split_line_to_commands, escaped_command_seperator2)
{
	char	**commands;

	commands = NULL;
	parser_lexer("123;456\\\\\\;123;456;", &commands);
	cr_assert(commands != NULL);
	cr_expect_str_eq(commands[0], "123");
	cr_expect_str_eq(commands[1], "456\\\\\\;123");
	cr_expect_str_eq(commands[2], "456");
	cr_expect_str_eq(commands[3], "");

	/* Do I have to free? forked program should exit here */
	ft_freearray(&commands);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(parser_strdup_command_from_line);

Test(parser_strdup_command_from_line, basic)
{
	char	*result;
	int		index;

	index = 0;
	result = parser_strdup_command_from_line("simple;command;line", &index);
	cr_assert(result != NULL);
	cr_expect_str_eq(result, "simple");

	/* Do I have to free? forked program should exit here */
	ft_strdel(&result);
}

Test(parser_strdup_command_from_line, moderate)
{
	char	*result;
	int		index;

	index = 0;
	result = parser_strdup_command_from_line("more\\;complicated;line", &index);
	cr_assert(result != NULL);
	cr_expect_str_eq(result, "more\\;complicated");

	/* Do I have to free? forked program should exit here */
	ft_strdel(&result);
}

Test(parser_strdup_command_from_line, quoted_command_seperator)
{
	char	*result;
	int		index;

	index = 0;
	result = parser_strdup_command_from_line("\"quoted;command;line\"", &index);
	cr_assert(result != NULL);
	cr_expect_str_eq(result, "quoted;command;line");

	/* Do I have to free? forked program should exit here */
	ft_strdel(&result);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(parser_command_len_from_line);

Test(parser_command_len_from_line, basic)
{
	int		index;

	index = 0;
	cr_expect_eq(parser_command_len_from_line("123456789", &index), 9);
	cr_expect_eq(parser_command_len_from_line("1;2", &index), 1);
}

Test(parser_command_len_from_line, escaped_command_seperator)
{
	int		index;

	index = 0;
	cr_expect_eq(parser_command_len_from_line("123456\\;9", &index), 9);
	cr_expect_eq(parser_command_len_from_line("1\\;\\;67", &index), 7);
}

Test(parser_command_len_from_line, quoted_command_seperator)
{
	int		index;

	index = 0;
	cr_expect_eq(parser_command_len_from_line("123\"5;7\"", &index), 6);
	cr_expect_eq(parser_command_len_from_line("\"2\"\\;;aaa", &index), 3);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(parser_total_commands_from_line);

Test(parser_total_commands_from_line, basic)
{
	cr_expect_eq(parser_total_commands_from_line("simple;command;line"), 3);
	cr_expect_eq(parser_total_commands_from_line("a;lot;of;commands;though;which;might;be;too;many;?"), 11);

	/* should this be 0 or 1? */
	cr_expect_eq(parser_total_commands_from_line(""), 1);
}

Test(parser_total_commands_from_line, escaped_command_seperator)
{
	cr_expect_eq(parser_total_commands_from_line("simple;commandline;with;escaped\\;semi;colon;line"), 6);
	cr_expect_eq(parser_total_commands_from_line("command\\;line\\;with;more\\;escaped;semi\\;colons"), 3);
}

Test(parser_total_commands_from_line, quoted_command_seperator)
{
	cr_expect_eq(parser_total_commands_from_line("commandline;with\";quoted;\"semi;colons"), 3);
	cr_expect_eq(parser_total_commands_from_line("\"nice;weird;\";quoted\"semi;colons\""), 2);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(is_char_escaped);

Test(is_char_escaped, basic)
{
	cr_expect_eq(is_char_escaped("\\n", 1), FUNCT_SUCCESS);
	cr_expect_eq(is_char_escaped("\\\\n", 2), FUNCT_FAILURE);
	cr_expect_eq(is_char_escaped("abc\\n", 4), FUNCT_SUCCESS);
	cr_expect_eq(is_char_escaped("abc\\\\n", 5), FUNCT_FAILURE);
}

Test(is_char_escaped, edge_cases)
{
	cr_expect_eq(is_char_escaped("\\\"\\n", 3), FUNCT_SUCCESS);
	cr_expect_eq(is_char_escaped("\\\"\\\\n", 4), FUNCT_FAILURE);
	cr_expect_eq(is_char_escaped("", 0), FUNCT_FAILURE);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(update_quote_status);

Test(update_quote_status, basic)
{
	char quote;
	
	quote = '\0';
	cr_expect_eq(update_quote_status("easy\"line\"", 3, &quote), 0);
	cr_expect_eq(quote, '\0');
	quote = '\0';
	cr_expect_eq(update_quote_status("easy\"line\"", 4, &quote), 1);
	cr_expect_eq(quote, '"');
	quote = '\0';
	cr_expect_eq(update_quote_status("easy\"line\"", 5, &quote), 0);
	cr_expect_eq(quote, '\0');
	quote = '\0';
	cr_expect_eq(update_quote_status("easy'line'", 3, &quote), 0);
	cr_expect_eq(quote, '\0');
	quote = '\0';
	cr_expect_eq(update_quote_status("easy'line'", 4, &quote), 1);
	cr_expect_eq(quote, '\'');
	quote = '\0';
	cr_expect_eq(update_quote_status("easy'line'", 5, &quote), 0);
	cr_expect_eq(quote, '\0');
}

Test(update_quote_status, edge_cases)
{
	char quote;
	
	quote = '\'';
	cr_expect_eq(update_quote_status("h'arde\\'rline'", 7, &quote), 0);
	cr_expect_eq(quote, '\'');
	quote = '\0';
	cr_expect_eq(update_quote_status("\\'harderline", 1, &quote), 0);
	cr_expect_eq(quote, '\0');
	quote = '"';
	cr_expect_eq(update_quote_status("\"harder'line\"", 7, &quote), 0);
	cr_expect_eq(quote, '"');
	quote = '\0';
	cr_expect_eq(update_quote_status("\\\"harder'line", 8, &quote), 1);
	cr_expect_eq(quote, '\'');
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(builtin_echo);

Test(builtin_echo, basic)
{
	/* Will need to use functions to change stdout to a tmp file from which
	we can strcmp the output and clear and reset afterwards */

	// builtin_echo({"echo", "-nEa", "\n"});
	// builtin_echo({"echo", "-nE", "\\n"});
	// builtin_echo({"echo", "-nEe", "\\\\abc\\t\\v\\r\\f\\n"});
	// builtin_echo({"echo", "-nEe"});
	// builtin_echo({"echo", "-E"});
	// builtin_echo({"echo"});
	cr_log_warn("Please read comments at builtin_echo testsuite (basic)");
}

Test(builtin_echo, return_values)
{
	/* Please add proper return values for echo (invalid flags/arguments etc) */

	// builtin_echo({"echo", "-nEaZ", "\n"});
	cr_log_warn("Please read comments at builtin_echo testsuite (return_values)");
}

		// return (test_ret_fail("test_prompt failed!"));

		// return (test_ret_fail("test_free_and_return_null failed!"));

		// return (test_ret_fail("test_get_environ_cpy failed!"));

		// return (test_ret_fail("test_param_to_env failed!"));

		// return (test_ret_fail("test_term_is_valid failed!"));

		// return (test_ret_fail("test_term_init_struct failed!"));

		// return (test_ret_fail("test_term_free_struct failed!"));

		// return (test_ret_fail("test_term_get_attributes failed!"));

		// return (test_ret_fail("test_parser_split_commands failed!"));

		// return (test_ret_fail("test_parser_strdup_command_from_line failed!"));

		// return (test_ret_fail("test_parser_command_len_from_line failed!"));

		// return (test_ret_fail("test_parser_total_commands_from_line failed!"));

		// return (test_ret_fail("test_is_char_escaped failed!"));

		// return (test_ret_fail("test_is_char_escaped failed!"));

		// return (test_ret_fail("test_echo failed!"));
