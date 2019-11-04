/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unit_test.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 16:37:32 by omulder        #+#    #+#                */
/*   Updated: 2019/10/29 12:37:30 by jbrinksm      ########   odam.nl         */
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
#include <errno.h>
#define INIT_VSHDATA data = ft_memalloc(sizeof(t_vshdata)); data->envlst = env_getlst(); data->curs = shell_init_vshdatacurs();	data->history = shell_init_vshdatahistory(); data->line = shell_init_vshdataline();	data->prompt = shell_init_vshdataprompt(); data->input = shell_init_vshdatainput();	data->hashtable = shell_init_vshdatahashtable(); data->alias = shell_init_vshdataalias(); data->term = term_init_struct(); data->termcaps = shell_init_vshdatatermcaps(); g_state = (t_state*)ft_memalloc(sizeof(t_state)); data->jobs = shell_init_vshdatajobs();

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
	t_vshdataterm	*term_p;

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
	t_vshdataterm	*term_p;

	term_p = term_init_struct();

	/* not sure how to have this as prerequisite as test any other way */
	cr_assert(term_p != NULL, "prerequisite failed: term_init_struct");

	term_free_struct(&term_p);
	cr_expect_eq(term_p, NULL);
}

/*
**------------------------------------------------------------------------------
*/

// TestSuite(term_get_attributes);

// Test(term_get_attributes, basic)
// {
// 	t_vshdataterm	*term_p;

// 	term_p = term_init_struct();

// 	/* not sure how to have this as prerequisite as test any other way */
// 	cr_assert(term_p != NULL, "prerequisite failed: term_init_struct");

// 	// cr_expect_eq(term_get_attributes(STDIN_FILENO, term_p), FUNCT_SUCCESS);
// 	cr_expect_eq(term_get_attributes(STDOUT_FILENO, term_p), FUNCT_SUCCESS);
// 	cr_expect_eq(term_get_attributes(STDERR_FILENO, term_p), FUNCT_SUCCESS);
// }

// Test(term_get_attributes, invalid_fd, .init=redirect_all_stdout)
// {
// 	t_vshdataterm	*term_p;

// 	cr_expect_eq(term_get_attributes(STDIN_FILENO, NULL), FUNCT_FAILURE);
// 	term_p = term_init_struct();

// 	/* not sure how to have this as prerequisite as test any other way */
// 	cr_assert(term_p != NULL, "prerequisite failed: term_init_struct");

// 	cr_expect_eq(term_get_attributes(10101, term_p), FUNCT_FAILURE);
// }

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
	t_vshdata	*data;

	
	INIT_VSHDATA
	data->line->line = strdup("lala");
	shell_close_unclosed_quotes(data);
	cr_expect_str_eq(data->line->line, "lala");
	data->line->line = strdup("lala''");
	shell_close_unclosed_quotes(data);
	cr_expect_str_eq(data->line->line, "lala''");
	data->line->line = strdup("lala\"\"");
	shell_close_unclosed_quotes(data);
	cr_expect_str_eq(data->line->line, "lala\"\"");
	data->line->line = strdup("lala'\"'");
	shell_close_unclosed_quotes(data);
	cr_expect_str_eq(data->line->line, "lala'\"'");
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
	lexer_error(NULL);
	cr_expect_stderr_eq_str("vsh: lexer: failed to allocate enough memory\n");
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
	lexer_error(NULL);
	cr_expect_stderr_eq_str("vsh: lexer: failed to allocate enough memory\n");
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
	lexer_error(NULL);
	cr_expect_stderr_eq_str("vsh: lexer: failed to allocate enough memory\n");
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
	lexer_error(NULL);
	cr_expect_stderr_eq_str("vsh: lexer: failed to allocate enough memory\n");
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
	ast = ast->left;
	cr_expect(ast->type == OR_IF);
	parser_astdel(&tmp_ast);
	cr_expect(tmp_ast == NULL);
}

/*
**------------------------------------------------------------------------------
*/

// TestSuite(exec_echo);

// Test(exec_echo, basic, .init=redirect_all_stdout)
// {
// 	t_tokenlst	*lst;
// 	t_ast		*ast;
// 	char 		*str;
// 	t_vshdata	*data;

	
// 	INIT_VSHDATA
// 	g_state->exit_code = 0;
// 	str = ft_strdup("echo hoi\n");
// 	lst = NULL;
// 	ast = NULL;
// 	data->envlst = env_getlst();
// 	cr_expect(lexer(&(str), &lst) == FUNCT_SUCCESS);
// 	cr_expect(parser_start(&lst, &ast) == FUNCT_SUCCESS);
// 	exec_complete_command(ast, data);
// 	cr_expect(g_state->exit_code == 0);
// 	cr_expect_stdout_eq_str("hoi\n");
// 	parser_astdel(&ast);
// }

// Test(exec_echo, basic2, .init=redirect_all_stdout)
// {
// 	t_tokenlst	*lst;
// 	t_ast		*ast;
// 	char 		*str;
// 	t_vshdata	*data;


// 	str = ft_strdup("echo \"Hi, this is a string\"\n");
// 	lst = NULL;
// 	ast = NULL;
	
// 	INIT_VSHDATA
// 	g_state->exit_code = 0;
// 	data->envlst = env_getlst();
// 	cr_expect(lexer(&(str), &lst) == FUNCT_SUCCESS);
// 	cr_expect(parser_start(&lst, &ast) == FUNCT_SUCCESS);
// 	exec_complete_command(ast, data);
// 	cr_expect(g_state->exit_code == 0);
// 	cr_expect_stdout_eq_str("Hi, this is a string\n");
// 	parser_astdel(&ast);
// }

/*
**------------------------------------------------------------------------------
*/

TestSuite(exec_find_bin);

Test(exec_find_bin, basic)
{
	char 		*str;
	char		*bin;
	t_vshdata	*data;

	
	INIT_VSHDATA
	data->envlst = (t_envlst*)ft_memalloc(sizeof(t_envlst));
	data->envlst->var = "PATH=./";
	data->envlst->type = ENV_EXTERN;
	data->envlst->next = NULL;
	hash_init(data);
	str = ft_strdup("vsh");
	exec_find_binary(str, data, &bin);
	cr_expect_str_eq(bin, ".//vsh");
	ft_strdel(&bin);
	ft_strdel(&str);
}

Test(exec_find_bin, basic2)
{
	char 		*str;
	char		*bin;
	t_vshdata	*data;

	
	INIT_VSHDATA
	data->envlst = (t_envlst*)ft_memalloc(sizeof(t_envlst));
	data->envlst->var = "PATH=/bin:./";
	data->envlst->type = ENV_EXTERN;
	data->envlst->next = NULL;
	hash_init(data);
	bin = NULL;
	str = ft_strdup("ls");
	exec_find_binary(str, data, &bin);
	cr_expect_str_eq(bin, "/bin/ls");
	ft_strdel(&bin);
	ft_strdel(&str);
}

Test(exec_find_bin, advanced)
{
	char 		*str;
	char		*bin;
	t_vshdata	*data;

	
	INIT_VSHDATA
	data->envlst = (t_envlst*)ft_memalloc(sizeof(t_envlst));
	data->envlst->var = "PATH=/Users/travis/.rvm/gems/ruby-2.4.2/bin:/Users/travis/.rvm/gems/ruby-2.4.2@global/bin:/Users/travis/.rvm/rubies/ruby-2.4.2/bin:/Users/travis/.rvm/bin:/Users/travis/bin:/Users/travis/.local/bin:/Users/travis/.nvm/versions/node/v6.11.4/bin:/bin:/usr/local/bin:/usr/bin:/usr/sbin:/sbin:/opt/X11/bin";
	data->envlst->type = ENV_EXTERN;
	data->envlst->next = NULL;
	hash_init(data);
	bin = NULL;
	str = ft_strdup("ls");
	exec_find_binary(str, data, &bin);
	cr_expect_str_eq(bin, "/bin/ls");
	ft_strdel(&bin);
	ft_strdel(&str);
}

Test(exec_find_bin, nopath, .init=redirect_all_stdout)
{
	char 		*str;
	char		*bin;
	t_vshdata	*data;
	
	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;
	
	INIT_VSHDATA
	data->envlst = (t_envlst*)ft_memalloc(sizeof(t_envlst));
	data->envlst->var = "PATH=";
	data->envlst->type = ENV_EXTERN;
	data->envlst->next = NULL;
	hash_init(data);
	bin = NULL;
	str = ft_strdup("ls");
	exec_find_binary(str, data, &bin);
	cr_expect(bin == NULL);
	ft_strdel(&bin);
	ft_strdel(&str);
}

// Test(exec_find_bin, execnonexistent, .init=redirect_all_stdout)
// {
// 	t_tokenlst	*lst;
// 	t_ast		*ast;
// 	char 		*str;
// 	t_vshdata	*data;

	
// 	printf("Yeeeeyn-1\n");
// 	INIT_VSHDATA
// 	g_state->exit_code = 0;
// 	printf("Yeeeeyn0\n");
// 	data->envlst = env_getlst();
// 	printf("Yeeeeyn1\n");
// 	hash_init(data);
// 	printf("Yeeeeyn2\n");
// 	str = ft_strdup("idontexist\n");
// 	printf("Yeeeeyn3\n");
// 	lst = NULL;
// 	ast = NULL;
// 	printf("Yeeeeyn4\n");
// 	cr_expect(lexer(&(str), &lst) == FUNCT_SUCCESS);
// 	cr_expect(parser_start(&lst, &ast) == FUNCT_SUCCESS);
// 	exec_complete_command(ast, data);
// 	cr_expect(g_state->exit_code == EXIT_NOTFOUND);
// 	cr_expect_stderr_eq_str("vsh: idontexist: command not found.\n");
// 	parser_astdel(&ast);
// }

TestSuite(builtin_export);

Test(builtin_export, basic_test)
{
	t_vshdata	*data;
	char		*args[3];

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;

	args[0] = "export";
	args[1] = "key=value";
	args[2] = NULL;
	
	INIT_VSHDATA
	data->envlst = env_getlst();
	builtin_export(args, data);
	while (data->envlst != NULL && ft_strnequ(data->envlst->var, "key", 3) == 0)
		data->envlst = data->envlst->next;
	cr_assert(data->envlst != NULL);
	cr_expect_str_eq(ft_itoa(g_state->exit_code), ft_itoa(EXIT_SUCCESS));
	cr_expect_str_eq(ft_itoa(data->envlst->type), ft_itoa(ENV_EXTERN));
	cr_expect_str_eq(data->envlst->var, "key=value");
}

Test(builtin_export, basic_test_n_option)
{
	t_vshdata	*data;
	char		*args[4];


	args[0] = "export";
	args[1] = "key=value";
	args[2] = NULL;
	
	INIT_VSHDATA
	g_state->exit_code = 0;
	data->envlst = env_getlst();
	builtin_export(args, data);
	args[0] = "export";
	args[1] = "-n";
	args[2] = "key=value";
	args[3] = NULL;
	builtin_export(args, data);
	while (data->envlst != NULL && ft_strnequ(data->envlst->var, "key", 3) == 0)
		data->envlst = data->envlst->next;
	cr_assert(data->envlst != NULL);
	cr_expect_str_eq(ft_itoa(g_state->exit_code), ft_itoa(EXIT_SUCCESS));
	cr_expect_str_eq(ft_itoa(data->envlst->type), ft_itoa(ENV_LOCAL));
	cr_expect_str_eq(data->envlst->var, "key=value");
}

Test(builtin_export, basic_output_error_test, .init=redirect_all_stdout)
{
	t_vshdata	*data;
	char		*args[3];

	INIT_VSHDATA
	g_state->exit_code = 0;
	args[0] = "export";
	args[1] = "key*=value";
	args[2] = NULL;
	data->envlst = env_getlst();
	builtin_export(args, data);
	cr_expect(g_state->exit_code == EXIT_WRONG_USE);
	cr_expect_stderr_eq_str("vsh: export: 'key*=value': not a valid identifier\n");
}

Test(builtin_export, basic_output_error_test2, .init=redirect_all_stdout)
{
	char		*args[3];
	t_vshdata	*data;

	INIT_VSHDATA
	g_state->exit_code = 0;
	args[0] = "export";
	args[1] = "-h";
	args[2] = NULL;
	data->envlst = env_getlst();
	builtin_export(args, data);
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


TestSuite(builtin_alias);

Test(builtin_alias, basic_test)
{
	t_aliaslst *aliaslst;
	char		*args[3];

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;
	aliaslst = NULL;
	args[0] = "alias";
	args[1] = "dit=dat";
	args[2] = NULL;
	builtin_alias(args, &aliaslst);
	cr_assert(aliaslst != NULL);
	cr_expect_str_eq(aliaslst->var, "dit=dat");
	cr_expect(g_state->exit_code == EXIT_SUCCESS);
}

Test(builtin_alias, basic_error_test, .init=redirect_all_stdout)
{
	t_aliaslst *aliaslst;
	char		*args[3];

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;
	aliaslst = NULL;
	args[0] = "alias";
	args[1] = "dit";
	args[2] = NULL;
	builtin_alias(args, &aliaslst);
	cr_assert(aliaslst == NULL);
	cr_expect_stderr_eq_str("vsh: alias: dit: not found\n");
	cr_expect(g_state->exit_code == EXIT_WRONG_USE);
}

Test(builtin_alias, basic_error_test2, .init=redirect_all_stdout)
{
	t_aliaslst *aliaslst;
	char		*args[3];

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;
	aliaslst = NULL;
	args[0] = "alias";
	args[1] = "-n";
	args[2] = NULL;
	builtin_alias(args, &aliaslst);
	cr_assert(aliaslst == NULL);
	cr_expect(g_state->exit_code == EXIT_WRONG_USE);
}

Test(builtin_unalias, basic_test)
{
	t_aliaslst *aliaslst;
	char		*args[3];

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;
	aliaslst = NULL;
	args[0] = "alias";
	args[1] = "dit=dat";
	args[2] = NULL;
	builtin_alias(args, &aliaslst);
	cr_assert(aliaslst != NULL);
	args[0] = "unalias";
	args[1] = "dit";
	args[2] = NULL;
	builtin_unalias(args, &aliaslst);
	cr_assert(aliaslst == NULL);
	cr_expect(g_state->exit_code == EXIT_SUCCESS);
}

Test(builtin_unalias, basic_error_test, .init=redirect_all_stdout)
{
	t_aliaslst *aliaslst;
	char		*args[3];

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;
	aliaslst = NULL;
	args[0] = "alias";
	args[1] = "dit=dat";
	args[2] = NULL;
	builtin_alias(args, &aliaslst);
	cr_assert(aliaslst != NULL);
	args[0] = "unalias";
	args[1] = "dat";
	args[2] = NULL;
	builtin_unalias(args, &aliaslst);
	cr_assert(aliaslst != NULL);
	cr_expect(g_state->exit_code == EXIT_FAILURE);
}

TestSuite(alias);

// Test(alias, basic_test)
// {
// 	char		*line;
// 	t_vshdata	*data;
// 	t_tokenlst	*token_lst;
// 	t_ast		*ast;

// 	line = ft_strdup("alias echo='echo hoi ; echo dit ' ; alias hoi=ditte ; alias dit=dat\n");
	
// 	INIT_VSHDATA
// 	g_state->exit_code = 0;
// 	data->envlst = env_getlst();
// 	cr_assert(data->envlst != NULL);
// 	token_lst = NULL;
// 	ast = NULL;
// 	cr_expect(lexer(&line, &token_lst) == FUNCT_SUCCESS);
// 	cr_assert(token_lst != NULL);
// 	cr_expect(parser_start(&token_lst, &ast) == FUNCT_SUCCESS);
// 	cr_assert(ast != NULL);
// 	cr_expect(exec_complete_command(ast, data) == FUNCT_SUCCESS);
// 	cr_expect_str_eq(data->alias->aliaslst->var, "dit=dat");
// 	line = ft_strdup("echo\n");
// 	lexer_tokenlstdel(&token_lst);
// 	cr_assert(line != NULL);
// 	cr_expect(lexer(&line, &token_lst) == FUNCT_SUCCESS);
// 	cr_assert(token_lst != NULL);
// 	cr_expect(alias_expansion(data, &token_lst, NULL) == FUNCT_SUCCESS);
// 	cr_assert(token_lst != NULL);
// 	cr_expect_str_eq(token_lst->next->next->value, "hoi");
// 	cr_expect_str_eq(token_lst->next->next->next->next->value, "echo");
// }

Test(alias, multi_line_test)
{
	char		*args[3];
	t_vshdata	*data;
	t_tokenlst	*token_lst;

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	g_state->exit_code = 0;
	data = ft_memalloc(sizeof(t_vshdata));
	data->curs = shell_init_vshdatacurs();
	data->history = shell_init_vshdatahistory();
	data->line = shell_init_vshdataline();
	data->prompt = shell_init_vshdataprompt();
	data->input = shell_init_vshdatainput();
	data->hashtable = shell_init_vshdatahashtable();
	data->alias = shell_init_vshdataalias();
	data->termcaps = shell_init_vshdatatermcaps();
	data->envlst = env_getlst();
	cr_assert(data->envlst != NULL);
	cr_assert(shell_init_files(data) != FUNCT_ERROR);
	cr_assert(alias_read_file(data) != FUNCT_ERROR);
	args[0] = "alias";
	args[1] = ft_strdup("echo=echo hoi\necho doei\n\n");
	args[2] = NULL;
	builtin_alias(args, &data->alias->aliaslst);
	cr_assert(g_state->exit_code == EXIT_SUCCESS);
	data->line->line = ft_strdup("echo\n");
	cr_assert(&data->line->line != NULL);
	token_lst = NULL;
	cr_expect(lexer(&data->line->line, &token_lst) == FUNCT_SUCCESS);
	cr_assert(token_lst != NULL);
	cr_expect(alias_expansion(data, &token_lst, NULL) == FUNCT_SUCCESS);
	cr_expect_str_eq(token_lst->next->next->value, "hoi");
	cr_expect(token_lst->next->next->next->type == SEMICOL);
}

TestSuite(alias_file);

Test(alias_file, basic_file_test)
{
	t_vshdata *data;
	char	*homedir;
	int		fd;

	
	INIT_VSHDATA
	g_state->exit_code = 0;
	data->envlst = env_getlst();
	data->alias->aliaslst = NULL;
	cr_assert(data->envlst != NULL);
	homedir = env_getvalue("HOME", data->envlst);
	cr_assert(homedir != NULL);
	data->alias->alias_file = ft_strjoin(homedir, "/.vsh_testalias");
	cr_assert(data->alias->alias_file != NULL);
	fd = open(data->alias->alias_file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	cr_assert(fd != -1);
	write(fd, "test=alias\n", 11);
	close(fd);
	alias_read_file(data);
	cr_expect_str_eq(data->alias->aliaslst->var, "test=alias");
	remove(data->alias->alias_file);
}

// TestSuite(replace_var);

// Test(replace_var, basic_test, .init=redirect_all_stdout)
// {
// 	char		*line;
// 	t_vshdata	*data;
// 	t_tokenlst	*token_lst;
// 	t_ast		*ast;

	
// 	INIT_VSHDATA
// 	g_state->exit_code = 0;
// 	line = ft_strdup("dit=dat ; hier=daar\n");
// 	data->alias->aliaslst = NULL;
// 	data->envlst = env_getlst();
// 	cr_assert(data->envlst != NULL);
// 	token_lst = NULL;
// 	ast = NULL;
// 	cr_expect(lexer(&line, &token_lst) == FUNCT_SUCCESS);
// 	cr_assert(token_lst != NULL);
// 	cr_expect(parser_start(&token_lst, &ast) == FUNCT_SUCCESS);
// 	cr_assert(ast != NULL);
// 	cr_expect(exec_complete_command(ast, data) == FUNCT_SUCCESS);
// 	cr_expect_str_eq(env_getvalue("dit", data->envlst), "dat");
// 	line = ft_strdup("echo $dit \"${hier}\"\n");
// 	cr_assert(line != NULL);
// 	lexer_tokenlstdel(&token_lst);
// 	cr_expect(lexer(&line, &token_lst) == FUNCT_SUCCESS);
// 	cr_assert(token_lst != NULL);
// 	cr_expect(parser_start(&token_lst, &ast) == FUNCT_SUCCESS);
// 	cr_assert(ast != NULL);
// 	cr_expect(exec_complete_command(ast, data) == FUNCT_SUCCESS);
// 	cr_expect_stdout_eq_str("dat daar\n");
// }

TestSuite(tilde_expansion);

Test(tilde_expansion, basic_test)
{
	t_vshdata	*data;
	t_ast		ast;
	char		*home;

	
	INIT_VSHDATA
	g_data = data;
	g_state->exit_code = 0;
	data->alias->aliaslst = NULL;
	data->envlst = env_getlst();
	cr_assert(data->envlst != NULL);
	home = getenv("HOME");
	cr_assert(home != NULL);
	ast.left = NULL;
	ast.right = NULL;
	ast.flags = T_FLAG_HASSPECIAL;
	ast.type = WORD;
	ast.value = ft_strdup("~/");
	cr_expect(expan_handle_variables(&ast, data->envlst) == FUNCT_SUCCESS);
	cr_expect_str_eq(ast.value, ft_strjoin(home, "/"));
	ast.flags = T_FLAG_HASSPECIAL;
	ast.type = ASSIGN;
	ast.value = ft_strdup("dit=~");
	cr_expect(expan_handle_variables(&ast, data->envlst) == FUNCT_SUCCESS);
	cr_expect_str_eq(ast.value, ft_strjoin("dit=", home));
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(deepfake);

Test(deepfake, fc_basic, .init=redirect_all_stdout)
{
	t_vshdata	*data;
	char **lines;

	INIT_VSHDATA
	g_data = data;
	history_add_item(data->history, "echo wauw");
	history_add_item(data->history, "echo wooh");
	history_add_item(data->history, "echo codam");
	history_add_item(data->history, "echo kippen");
	history_add_item(data->history, "echo hoi\ndoei");
	lines = (char**)ft_memalloc(sizeof(char*) * 11);
	lines[0] = ft_strdup("fc -l");
	lines[1] = ft_strdup("fc -lr -2");
	lines[2] = ft_strdup("fc -l 1 -3");
	lines[3] = ft_strdup("fc -e cat -4");
	lines[4] = ft_strdup("fc -l echo -5");
	lines[5] = ft_strdup("fc -s hoi=doei -6");
	lines[6] = ft_strdup("fc -ln 200 -200");
	lines[7] = ft_strdup("fc -e cat");
	lines[8] = ft_strdup("fc -s wauw=wow 1");
	data->fc_flags |= FC_PRINT_CMD;
	data->fc_flags |= FC_SET_HIST;
	shell_lines_exec(data, lines);
	ft_strarrdel(&lines);
	cr_expect(g_state->exit_code == EXIT_SUCCESS);
	shell_one_line(data, "fc -l error");
	cr_expect(g_state->exit_code == EXIT_FAILURE);
}

Test(deepfake, history_basic, .init=redirect_all_stdout)
{
	t_vshdata	*data;
	char **lines;

	INIT_VSHDATA
	g_data = data;
	history_add_item(data->history, "echo wauw");
	history_add_item(data->history, "echo wooh");
	history_add_item(data->history, "echo codam");
	history_add_item(data->history, "echo kippen");
	history_add_item(data->history, "echo hoi\ndoei");
	lines = (char**)ft_memalloc(sizeof(char*) * 11);
	lines[0] = ft_strdup("history");
	lines[1] = ft_strdup("echo !-2");
	lines[2] = ft_strdup("echo !!");
	lines[3] = ft_strdup("echo !echo");
	lines[4] = ft_strdup("echo !2");
	data->fc_flags |= FC_PRINT_CMD;
	data->fc_flags |= FC_SET_HIST;
	shell_lines_exec(data, lines);
	ft_strarrdel(&lines);
	cr_expect(g_state->exit_code == EXIT_SUCCESS);
	history_index_change_up(data->history);
	history_index_change_down(data->history);
}
