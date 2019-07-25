/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unit_test.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:37:32 by omulder        #+#    #+#                */
/*   Updated: 2019/07/25 16:08:03 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	General note: We have to make sure that we redirect the STDOUT to some sort
**	of file, so that we don't destroy the test_suite output.
**	(Also, see the comments at builtin_echo.)
*/

#include "vsh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include "vsh_history.h"

void redirect_all_stdout(void)
{
        cr_redirect_stdout();
        cr_redirect_stderr();
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(term_is_valid);

Test(term_is_valid, basic, .init=redirect_all_stdout)
{
	t_envlst	lst1;
	t_envlst	lst2;

	lst1.var = "TERM=non_valid_term";
	lst2.var = "TERM=vt100";
	lst1.type = ENV_EXTERN;
	lst2.type = ENV_EXTERN;
	lst1.next = NULL;
	lst2.next = NULL;
	cr_expect_eq(term_is_valid(&lst1), FUNCT_FAILURE);
	cr_expect_eq(term_is_valid(&lst2), FUNCT_SUCCESS);
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

TestSuite(term_get_attributes);

Test(term_get_attributes, basic)
{
	t_term	*term_p;

	term_p = term_init_struct();

	/* not sure how to have this as prerequisite as test any other way */
	cr_assert(term_p != NULL, "prerequisite failed: term_init_struct");

	// cr_expect_eq(term_get_attributes(STDIN_FILENO, term_p), FUNCT_SUCCESS);
	cr_expect_eq(term_get_attributes(STDOUT_FILENO, term_p), FUNCT_SUCCESS);
	cr_expect_eq(term_get_attributes(STDERR_FILENO, term_p), FUNCT_SUCCESS);
}

Test(term_get_attributes, invalid_fd, .init=redirect_all_stdout)
{
	t_term	*term_p;

	cr_expect_eq(term_get_attributes(STDIN_FILENO, NULL), FUNCT_FAILURE);
	term_p = term_init_struct();

	/* not sure how to have this as prerequisite as test any other way */
	cr_assert(term_p != NULL, "prerequisite failed: term_init_struct");

	cr_expect_eq(term_get_attributes(10101, term_p), FUNCT_FAILURE);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(tools_is_char_escaped);

Test(tools_is_char_escaped, basic)
{
	cr_expect_eq(tools_is_char_escaped("\\n", 1), true);
	cr_expect_eq(tools_is_char_escaped("\\\\n", 2), false);
	cr_expect_eq(tools_is_char_escaped("abc\\n", 4), true);
	cr_expect_eq(tools_is_char_escaped("abc\\\\n", 5), false);
}

Test(tools_is_char_escaped, edge_cases)
{
	cr_expect_eq(tools_is_char_escaped("\\\"\\n", 3), true);
	cr_expect_eq(tools_is_char_escaped("\\\"\\\\n", 4), false);
	cr_expect_eq(tools_is_char_escaped("", 0), false);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(shell_quote_checker_find_quote);

Test(shell_quote_checker_find_quote, basic)
{
	char *line;

	line = "A simple \"line\"";
	cr_expect_eq(shell_quote_checker_find_quote(line), '\0');
	line = "A simple \"line";
	cr_expect_eq(shell_quote_checker_find_quote(line), '"');
	line = "A simple line";
	cr_expect_eq(shell_quote_checker_find_quote(line), '\0');
	line = "A simple line\"";
	cr_expect_eq(shell_quote_checker_find_quote(line), '"');
	line = "A simple 'line'";
	cr_expect_eq(shell_quote_checker_find_quote(line), '\0');
	line = "A simple 'line";
	cr_expect_eq(shell_quote_checker_find_quote(line), '\'');
	line = "A simple line";
	cr_expect_eq(shell_quote_checker_find_quote(line), '\0');
	line = "A simple line'";
	cr_expect_eq(shell_quote_checker_find_quote(line), '\'');
}

Test(shell_quote_checker_find_quote, both_quotes)
{
	char *line;

	line = "A simple \"line\'";
	cr_expect_eq(shell_quote_checker_find_quote(line), '"');
	line = "A simple 'line\"";
	cr_expect_eq(shell_quote_checker_find_quote(line), '\'');
	line = "A simple ''line\"";
	cr_expect_eq(shell_quote_checker_find_quote(line), '"');
	line = "'A simple 'line\"";
	cr_expect_eq(shell_quote_checker_find_quote(line), '"');
	line = "A simple 'line\"\"";
	cr_expect_eq(shell_quote_checker_find_quote(line), '\'');
	line = "A simple 'line\"'\"'";
	cr_expect_eq(shell_quote_checker_find_quote(line), '"');
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(shell_quote_checker);

/*	
**	Not sure how to test this properly yet, since you need input if
**	the quoting isn't correct.
*/

Test(shell_quote_checker, basic)
{
	char	*line;
	int		status;

	line = strdup("lala");
	shell_quote_checker(&line, &status);
	cr_expect_str_eq(line, "lala");
	ft_strdel(&line);
	line = strdup("lala''");
	shell_quote_checker(&line, &status);
	cr_expect_str_eq(line, "lala''");
	ft_strdel(&line);
	line = strdup("lala\"\"");
	shell_quote_checker(&line, &status);
	cr_expect_str_eq(line, "lala\"\"");
	ft_strdel(&line);
	line = strdup("lala'\"'");
	shell_quote_checker(&line, &status);
	cr_expect_str_eq(line, "lala'\"'");
	ft_strdel(&line);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(builtin_echo);

Test(builtin_echo, basic, .init=redirect_all_stdout)
{
	char	**args;

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;

	args = ft_strsplit("echo|-nEe|\\\\test\\a\\t\\v\\r\\n\\b\\f\\E", '|');
	g_state->exit_code = INT_MIN;
	builtin_echo(args);
	cr_expect(g_state->exit_code == 0);
	ft_strarrdel(&args);

	g_state->exit_code = 0;
	args = ft_strsplit("echo|-Eea|\n", '|');
	g_state->exit_code = INT_MIN;
	builtin_echo(args);
	cr_expect(g_state->exit_code == 0);
	ft_strarrdel(&args);

	g_state->exit_code = 0;
	args = ft_strsplit("echo|-nEe", '|');
	g_state->exit_code = INT_MIN;
	builtin_echo(args);
	cr_expect(g_state->exit_code == 0);
	ft_strarrdel(&args);

	g_state->exit_code = 0;
	args = ft_strsplit("echo|-E", '|');
	g_state->exit_code = INT_MIN;
	builtin_echo(args);
	cr_expect(g_state->exit_code == 0);

	cr_expect_stdout_eq_str("\\test\a\t\v\r\n\b\f\e-Eea \n\n\n");
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(env_getvalue);

Test(env_getvalue, basic)
{
	t_envlst	*envlst;
	t_envlst	lst1;
	t_envlst	lst2;
	t_envlst	lst3;

	envlst = &lst1;
	lst1.var = "LOL=didi";
	lst2.var = "PAT=lolo";
	lst3.var = "PATH=lala";
	lst1.type = ENV_EXTERN;
	lst2.type = ENV_EXTERN;
	lst3.type = ENV_EXTERN;
	lst1.next = &lst2;
	lst2.next = &lst3;
	lst3.next = NULL;
	cr_expect_str_eq(env_getvalue("PATH", envlst), "lala");
	cr_expect(env_getvalue("NOEXIST", envlst) == NULL);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(lexer_error, .init=redirect_all_stdout);

Test(lexer_error, one_item)
{
	t_tokenlst	*lst;

	lst = NULL;
	lexer_tokenlstaddback(&lst, START, NULL, 0);
	lexer_error(&lst, NULL);
	cr_expect(lst == NULL);
	cr_expect_stderr_eq_str("vsh: lexer: malloc error\n");
}

Test(lexer_error, long_list)
{
	t_tokenlst	*lst;

	lst = NULL;
	lexer_tokenlstaddback(&lst, START, NULL, 0);
	lexer_tokenlstaddback(&lst, WORD, ft_strdup("testword"), 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, WORD, ft_strdup("testword"), 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, IO_NUMBER, ft_strdup("235235"), 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, WORD, ft_strdup("testword"), 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, IO_NUMBER, ft_strdup("12351235"), 0);
	lexer_tokenlstaddback(&lst, IO_NUMBER, ft_strdup("1235135"), 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, WORD, ft_strdup("testword"), 0);
	lexer_tokenlstaddback(&lst, IO_NUMBER, ft_strdup("1512351"), 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, WORD, ft_strdup("testword"), 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, END, NULL, 0);
	lexer_error(&lst, NULL);
	cr_expect(lst == NULL);
	cr_expect_stderr_eq_str("vsh: lexer: malloc error\n");
}

Test(lexer_error, all_items)
{
	t_tokenlst	*lst;

	lst = NULL;
	lexer_tokenlstaddback(&lst, START, NULL, 0);
	lexer_tokenlstaddback(&lst, WORD, ft_strdup("testword"), 0);
	lexer_tokenlstaddback(&lst, IO_NUMBER, ft_strdup("testword"), 0);
	lexer_tokenlstaddback(&lst, ERROR, NULL, 0);
	lexer_tokenlstaddback(&lst, ASSIGN, ft_strdup("testword"), 0);
	lexer_tokenlstaddback(&lst, AND_IF, NULL, 0);
	lexer_tokenlstaddback(&lst, OR_IF, NULL, 0);
	lexer_tokenlstaddback(&lst, DLESS, NULL, 0);
	lexer_tokenlstaddback(&lst, DGREAT, NULL, 0);
	lexer_tokenlstaddback(&lst, SLESS, NULL, 0);
	lexer_tokenlstaddback(&lst, SGREAT, NULL, 0);
	lexer_tokenlstaddback(&lst, LESSAND, NULL, 0);
	lexer_tokenlstaddback(&lst, GREATAND, NULL, 0);
	lexer_tokenlstaddback(&lst, BG, NULL, 0);
	lexer_tokenlstaddback(&lst, PIPE, NULL, 0);
	lexer_tokenlstaddback(&lst, SEMICOL, NULL, 0);
	lexer_tokenlstaddback(&lst, NEWLINE, NULL, 0);
	lexer_tokenlstaddback(&lst, END,  NULL, 0);
	lexer_error(&lst, NULL);
	cr_expect(lst == NULL);
	cr_expect_stderr_eq_str("vsh: lexer: malloc error\n");
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(lexer_tokenlstaddback, .init=redirect_all_stdout);

Test(lexer_tokenlstaddback, invalid_values)
{
	t_tokenlst	*lst;

	lst = NULL;
	lexer_tokenlstaddback(&lst, END, ft_strdup("testword"), 0);
	lexer_tokenlstaddback(&lst, WORD, ft_strdup("testword"), 0);
	lexer_tokenlstaddback(&lst, ERROR, NULL, 0);
	lexer_tokenlstaddback(&lst, ERROR, NULL, 0);
	lexer_tokenlstaddback(&lst, ASSIGN, NULL, 0);
	lexer_tokenlstaddback(&lst, AND_IF, ft_strdup("testword"), 0);
	lexer_tokenlstaddback(&lst, OR_IF, NULL, 0);
	lexer_tokenlstaddback(&lst, LESSAND, NULL, 0);
	lexer_tokenlstaddback(&lst, ERROR, NULL, 0);
	lexer_tokenlstaddback(&lst, SLESS, NULL, 0);
	lexer_tokenlstaddback(&lst, SGREAT, ft_strdup("testword"), 0);
	lexer_tokenlstaddback(&lst, LESSAND, NULL, 0);
	lexer_tokenlstaddback(&lst, GREATAND, NULL, 0);
	lexer_tokenlstaddback(&lst, BG, NULL, 0);
	lexer_tokenlstaddback(&lst, GREATAND, NULL, 0);
	lexer_tokenlstaddback(&lst, END, NULL, 0);
	lexer_tokenlstaddback(&lst, START, NULL, 0);
	lexer_tokenlstaddback(&lst, ERROR, ft_strdup("testword"), 0);
	lexer_error(&lst, NULL);
	cr_expect(lst == NULL);
	cr_expect_stderr_eq_str("vsh: lexer: malloc error\n");
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(lexer);

Test(lexer, basic)
{
	t_tokenlst	*lst;
	t_tokenlst	*tmp;
	char 		*str;

	str = ft_strdup("HOME=/ ls -la || ls 2>file \"Documents\";");
	cr_assert(str != NULL);
	lst = NULL;
	cr_expect(lexer(&str, &lst) == FUNCT_SUCCESS);
	tmp = lst;
	cr_expect(lst->type == START);
	cr_expect(lst->value == NULL);
	lst = lst->next;
	cr_expect(lst->type == ASSIGN);
	cr_expect_str_eq(lst->value, "HOME=/");
	lst = lst->next;
	cr_expect(lst->type == WORD);
	cr_expect_str_eq(lst->value, "ls");
	lst = lst->next;
	cr_expect(lst->type == WORD);
	cr_expect_str_eq(lst->value, "-la");
	lst = lst->next;
	cr_expect(lst->type == OR_IF);
	cr_expect(lst->value == NULL);
	lst = lst->next;
	cr_expect(lst->type == WORD);
	cr_expect_str_eq(lst->value, "ls");
	lst = lst->next;
	cr_expect(lst->type == IO_NUMBER);
	cr_expect_str_eq(lst->value, "2");
	lst = lst->next;
	cr_expect(lst->type == SGREAT);
	cr_expect(lst->value == NULL);
	lst = lst->next;
	cr_expect(lst->type == WORD);
	cr_expect_str_eq(lst->value, "file");
	lst = lst->next;
	cr_expect(lst->type == WORD);
	cr_expect_str_eq(lst->value, "\"Documents\"");
	lst = lst->next;
	cr_expect(lst->type == SEMICOL);
	lst = lst->next;
	cr_expect(lst->type == END);
	cr_expect(lst->value == NULL);
	lexer_tokenlstdel(&tmp);
}

TestSuite(parser);

Test(parser, basic)
{
	t_tokenlst	*lst;
	t_ast		*ast;
	t_ast		*tmp_ast;
	char 		*str;

	str = ft_strdup("HOME=/ ls -la || ls 2>file \"Documents\";\n");
	lst = NULL;
	ast = NULL;
	cr_expect(lexer(&str, &lst) == FUNCT_SUCCESS);
	cr_expect(parser_start(&lst, &ast) == FUNCT_SUCCESS);
	tmp_ast = ast;
	cr_expect(ast->type == SEMICOL);
	ast = ast->child;
	cr_expect(ast->type == OR_IF);
	parser_astdel(&tmp_ast);
	cr_expect(tmp_ast == NULL);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(command_exit);

Test(command_exec, basic, .init=redirect_all_stdout)
{
	t_tokenlst	*lst;
	t_ast		*ast;
	char 		*str;
	t_vshdata	vshdata;

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;

	str = ft_strdup("ls\n");
	lst = NULL;
	ast = NULL;
	vshdata.envlst = env_getlst();
	cr_expect(lexer(&(str), &lst) == FUNCT_SUCCESS);
	cr_expect(parser_start(&lst, &ast) == FUNCT_SUCCESS);
	exec_start(ast, &vshdata, 0);
	cr_expect(g_state->exit_code == EXIT_SUCCESS);
	parser_astdel(&ast);
}

/*
**------------------------------------------------------------------------------
*/
/* TestSuite(history_check);

Test(history_check, history_to_file)
{
	int		fd;
	char	*array[4];
	char	buf[22];
	int 	ret;

	ft_bzero(buf, 22);
	array[0] = "check1";
	array[1] = "check2";
	array[2] = "check3";
	array[3] = NULL;
	history = array;
	cr_expect(history_to_file() == FUNCT_SUCCESS);
	fd = open("/tmp/.vsh_history", O_RDONLY);
	cr_expect(fd > 0);
	ret = read(fd, buf, 22);
	cr_expect(ret == 21);
	cr_expect(ft_strcmp(buf, "check1\ncheck2\ncheck3\n") == 0);
}

Test(history_check, get_file_content)
{
	char	*array[4];

	array[0] = ft_strdup("check1");
	array[1] = ft_strdup("check2");
	array[2] = ft_strdup("check3");
	array[3] = NULL;
	history = array;
	cr_expect(history_to_file() == FUNCT_SUCCESS);
	cr_expect(history_get_file_content() == FUNCT_SUCCESS);
	cr_expect_str_eq("check1", history[0]);
	cr_expect_str_eq("check2", history[1]);
	cr_expect_str_eq("check3", history[2]);
	cr_expect(history[3] == NULL);
} 

TestSuite(history_output);

Test(history_check, history_print, .init=redirect_all_stdout)
{
	char	*array[4];

	history = array;
	array[0] = ft_strdup("check1");
	array[1] = ft_strdup("check2");
	array[2] = ft_strdup("check3");
	array[3] = NULL;
	cr_expect(history_to_file() == FUNCT_SUCCESS);
	cr_expect(history_get_file_content() == FUNCT_SUCCESS);
	history_print();
	cr_expect_stdout_eq_str("    0  check1\n    1  check2\n    2  check3\n");
} */
/*
**------------------------------------------------------------------------------
*/

TestSuite(exec_echo);

Test(exec_echo, basic, .init=redirect_all_stdout)
{
	t_tokenlst	*lst;
	t_ast		*ast;
	char 		*str;
	t_vshdata	vshdata;

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;

	str = ft_strdup("echo hoi\n");
	lst = NULL;
	ast = NULL;
	vshdata.envlst = env_getlst();
	cr_expect(lexer(&(str), &lst) == FUNCT_SUCCESS);
	cr_expect(parser_start(&lst, &ast) == FUNCT_SUCCESS);
	exec_start(ast, &vshdata, 0);
	cr_expect(g_state->exit_code == 0);
	cr_expect_stdout_eq_str("hoi\n");
	parser_astdel(&ast);
}

Test(exec_echo, basic2, .init=redirect_all_stdout)
{
	t_tokenlst	*lst;
	t_ast		*ast;
	char 		*str;
	t_vshdata	vshdata;

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;

	str = ft_strdup("echo \"Hi, this is a string\"\n");
	lst = NULL;
	ast = NULL;
	vshdata.envlst = env_getlst();
	cr_expect(lexer(&(str), &lst) == FUNCT_SUCCESS);
	cr_expect(parser_start(&lst, &ast) == FUNCT_SUCCESS);
	exec_start(ast, &vshdata, 0);
	cr_expect(g_state->exit_code == 0);
	cr_expect_stdout_eq_str("Hi, this is a string\n");
	parser_astdel(&ast);
} 

/*
**------------------------------------------------------------------------------
*/

TestSuite(exec_cmd);

Test(exec_cmd, basic, .init=redirect_all_stdout)
{
	t_tokenlst	*lst;
	t_ast		*ast;
	char 		*str;
	char 		*cwd;
	t_vshdata	vshdata;

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;

	str = ft_strdup("/bin/pwd\n");
	cwd = getcwd(NULL, 0);
	lst = NULL;
	ast = NULL;
	vshdata.envlst = env_getlst();
	cr_expect(lexer(&(str), &lst) == FUNCT_SUCCESS);
	cr_expect(parser_start(&lst, &ast) == FUNCT_SUCCESS);
	exec_start(ast, &vshdata, 0);
	cr_expect(g_state->exit_code == 0);
	ft_strdel(&str);
	str = ft_strjoin(cwd, "\n");
	cr_expect_stdout_eq_str(str);
	ft_strdel(&str);
	ft_strdel(&cwd);
	parser_astdel(&ast);
}

Test(exec_cmd, basic2, .init=redirect_all_stdout)
{
	t_tokenlst	*lst;
	t_ast		*ast;
	char 		*str;
	t_vshdata	vshdata;

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;

	str = ft_strdup("/bin/echo hoi\n");
	lst = NULL;
	ast = NULL;
	vshdata.envlst = env_getlst();
	cr_expect(lexer(&(str), &lst) == FUNCT_SUCCESS);
	cr_expect(parser_start(&lst, &ast) == FUNCT_SUCCESS);
	exec_start(ast, &vshdata, 0);
	cr_expect(g_state->exit_code == 0);
	cr_expect_stdout_eq_str("hoi\n");
	parser_astdel(&ast);
} 

/*
**------------------------------------------------------------------------------
*/

TestSuite(exec_find_bin);

Test(exec_find_bin, basic)
{
	char 		*str;
	char		*bin;
	t_envlst	lst;

	lst.var = "PATH=./";
	lst.type = ENV_EXTERN;
	lst.next = NULL;
	str = ft_strdup("vsh");
	bin = exec_find_binary(str, &lst);
	cr_expect_str_eq(bin, ".//vsh");
	ft_strdel(&bin);
	ft_strdel(&str);
}

Test(exec_find_bin, basic2)
{
	char 		*str;
	char		*bin;
	t_envlst	lst;

	lst.var = "PATH=/bin:./";
	lst.type = ENV_EXTERN;
	lst.next = NULL;
	str = ft_strdup("ls");
	bin = exec_find_binary(str, &lst);
	cr_expect_str_eq(bin, "/bin/ls");
	ft_strdel(&bin);
	ft_strdel(&str);
}

Test(exec_find_bin, advanced)
{
	char 		*str;
	char		*bin;
	t_envlst	lst;

	lst.var = "PATH=/Users/travis/.rvm/gems/ruby-2.4.2/bin:/Users/travis/.rvm/gems/ruby-2.4.2@global/bin:/Users/travis/.rvm/rubies/ruby-2.4.2/bin:/Users/travis/.rvm/bin:/Users/travis/bin:/Users/travis/.local/bin:/Users/travis/.nvm/versions/node/v6.11.4/bin:/bin:/usr/local/bin:/usr/bin:/usr/sbin:/sbin:/opt/X11/bin";
	lst.type = ENV_EXTERN;
	lst.next = NULL;
	str = ft_strdup("ls");
	bin = exec_find_binary(str, &lst);
	cr_expect_str_eq(bin, "/bin/ls");
	ft_strdel(&bin);
	ft_strdel(&str);
}

Test(exec_find_bin, nopath)
{
	char 		*str;
	char		*bin;
	t_envlst	lst;

	lst.var = "PATH=";
	lst.type = ENV_EXTERN;
	lst.next = NULL;
	str = ft_strdup("ls");
	bin = exec_find_binary(str, &lst);
	cr_expect(bin == NULL);
	ft_strdel(&bin);
	ft_strdel(&str);
}

Test(exec_find_bin, execution, .init=redirect_all_stdout)
{
	t_tokenlst	*lst;
	t_ast		*ast;
	char 		*str;
	t_vshdata	vshdata;

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;

	vshdata.envlst = env_getlst();
	str = ft_strdup("ls vsh\n");
	lst = NULL;
	ast = NULL;
	cr_expect(lexer(&(str), &lst) == FUNCT_SUCCESS);
	cr_expect(parser_start(&lst, &ast) == FUNCT_SUCCESS);
	exec_start(ast, &vshdata, 0);
	cr_expect(g_state->exit_code == EXIT_SUCCESS);
	cr_expect_stdout_eq_str("vsh\n");
	parser_astdel(&ast);
}

Test(exec_find_bin, execnonexistent, .init=redirect_all_stdout)
{
	t_tokenlst	*lst;
	t_ast		*ast;
	char 		*str;
	t_vshdata	vshdata;

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;

	vshdata.envlst = env_getlst();
	str = ft_strdup("idontexist\n");
	lst = NULL;
	ast = NULL;
	cr_expect(lexer(&(str), &lst) == FUNCT_SUCCESS);
	cr_expect(parser_start(&lst, &ast) == FUNCT_SUCCESS);
	exec_start(ast, &vshdata, 0);
	cr_expect(g_state->exit_code == EXIT_NOTFOUND);
	cr_expect_stdout_eq_str("idontexist: Command not found.\n");
	parser_astdel(&ast);
}

TestSuite(builtin_export);

Test(builtin_export, basic_test)
{
	t_envlst    *envlst;
	char		*args[3];

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;

	args[0] = "export";
	args[1] = "key=value";
	args[2] = NULL;
	envlst = env_getlst();
	builtin_export(args, envlst);
	while (envlst != NULL && ft_strnequ(envlst->var, "key", 3) == 0)
		envlst = envlst->next;
	cr_assert(envlst != NULL);
	cr_expect_str_eq(ft_itoa(g_state->exit_code), ft_itoa(EXIT_SUCCESS));
	cr_expect_str_eq(ft_itoa(envlst->type), ft_itoa(ENV_EXTERN));
	cr_expect_str_eq(envlst->var, "key=value");
}

Test(builtin_export, basic_test_n_option)
{
	t_envlst    *envlst;
	char		*args[4];

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;

	args[0] = "export";
	args[1] = "key=value";
	args[2] = NULL;
	envlst = env_getlst();
	builtin_export(args, envlst);
	args[0] = "export";
	args[1] = "-n";
	args[2] = "key=value";
	args[3] = NULL;
	builtin_export(args, envlst);
	while (envlst != NULL && ft_strnequ(envlst->var, "key", 3) == 0)
		envlst = envlst->next;
	cr_assert(envlst != NULL);
	cr_expect_str_eq(ft_itoa(g_state->exit_code), ft_itoa(EXIT_SUCCESS));
	cr_expect_str_eq(ft_itoa(envlst->type), ft_itoa(ENV_LOCAL));
	cr_expect_str_eq(envlst->var, "key=value");
}

Test(builtin_export, basic_output_error_test, .init=redirect_all_stdout)
{
	t_envlst    *envlst;
	char		*args[3];

	g_state = (t_state*)ft_memalloc(sizeof(t_state));

	g_state->exit_code = 0;
	args[0] = "export";
	args[1] = "key*=value";
	args[2] = NULL;
	envlst = env_getlst();
	builtin_export(args, envlst);
	cr_expect(g_state->exit_code == EXIT_WRONG_USE);
	cr_expect_stdout_eq_str("vsh: export: 'key*=value': not a valid identifier\n");
}

Test(builtin_export, basic_output_error_test2, .init=redirect_all_stdout)
{
	t_envlst    *envlst;
	char		*args[3];

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	
	g_state->exit_code = 0;
	args[0] = "export";
	args[1] = "-h";
	args[2] = NULL;
	envlst = env_getlst();
	builtin_export(args, envlst);
	cr_expect(g_state->exit_code == EXIT_WRONG_USE);
}

TestSuite(env_sort);

Test(env_sort, basic_test)
{
	t_envlst    *envlst;

	envlst = env_lstnew("HEAD", ENV_HEAD);
	env_lstaddback(&envlst, env_lstnew("def", ENV_EXTERN));
	env_lstaddback(&envlst, env_lstnew("abc", ENV_EXTERN));
	env_sort(envlst);
	cr_assert(envlst != NULL);
	cr_expect_str_eq(envlst->next->var, "abc");
	cr_expect_str_eq(envlst->next->next->var, "def");
}
