/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_tests.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/04 16:38:04 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/05 12:51:07 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

TestSuite(parser_lexer);

Test(parser_lexer, basic)
{
	t_list	*expected;
	t_list	*lst = NULL;
	t_list	*content1;
	t_list	*content2;
	char	*str1;
	char	*str2;
	t_list	*exp_content;
	t_list	*lst_content;

	str1 = ft_strdup("string1\\\\");
	str2 = ft_strdup("string2");
	content1 = ft_lstnew(str1, ft_strlen(str1) + 1);
	content1->next = ft_lstnew(str2, ft_strlen(str2) + 1);
	content2 = ft_lstnew(str2, ft_strlen(str2) + 1);

	expected = ft_lstnew(NULL, 0);
	expected->content = content1;
	expected->next = ft_lstnew(NULL, 0);
	expected->next->content = content2;

	parser_lexer("string1\\\\ string2;string2", &lst);

	exp_content = expected->content;
	lst_content = lst->content;
	cr_expect_str_eq(lst_content->content, exp_content->content);
	cr_expect_str_eq(lst_content->next->content, exp_content->next->content);
	cr_expect_eq(lst_content->next->next, NULL);

	exp_content = expected->next->content;
	lst_content = lst->next->content;
	cr_expect_str_eq(lst_content->content, exp_content->content);
	cr_expect_eq(lst_content->next, NULL);
}

Test(parser_lexer, escaped_or_quoted)
{
	t_list	*expected;
	t_list	*lst = NULL;
	t_list	*content1;
	t_list	*content2;
	char	*str1;
	char	*str2;
	char	*str3;
	t_list	*exp_content;
	t_list	*lst_content;

	str1 = ft_strdup("text;something");
	str2 = ft_strdup(";lala;ala");
	str3 = ft_strdup("more\\\\wei rd;shit");
	content1 = ft_lstnew(str1, ft_strlen(str1) + 1);
	content1->next = ft_lstnew(str2, ft_strlen(str2) + 1);
	content2 = ft_lstnew(str3, ft_strlen(str3) + 1);

	expected = ft_lstnew(NULL, 0);
	expected->content = content1;
	expected->next = ft_lstnew(NULL, 0);
	expected->next->content = content2;

	parser_lexer("text\\;something \\;\"lala\\;ala\";more\\\\wei\\ rd\\;shit", &lst);

	exp_content = expected->content;
	lst_content = lst->content;
	cr_expect_str_eq(lst_content->content, exp_content->content);
	cr_expect_str_eq(lst_content->next->content, exp_content->next->content);
	cr_expect_eq(lst_content->next->next, NULL);

	exp_content = expected->next->content;
	lst_content = lst->next->content;
	cr_expect_str_eq(lst_content->content, exp_content->content);
	cr_expect_eq(lst_content->next, NULL);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(parser_split_line_to_commands);

Test(parser_split_line_to_commands, basic)
{
	t_list	*lst;
	char	*content;

	lst = parser_split_line_to_commands("\"\";1'22'3'4';'1;';");
	content = lst->content;
	cr_expect_str_eq(content, "\"\"");
	content = lst->next->content;
	cr_expect_str_eq(content, "1'22'3'4'");
	content = lst->next->next->content;
	cr_expect_str_eq(content, "'1;'");
	cr_expect_eq(lst->next->next->next, NULL);
}

Test(parser_split_line_to_commands, escaped_command_seperator)
{
	t_list	*lst;
	char	*content;

	lst = parser_split_line_to_commands("lalalaffffdsdg;asdgasdgas\\;dg as;dgas gas\\\";@");
	content = lst->content;
	cr_expect_str_eq(content, "lalalaffffdsdg");
	content = lst->next->content;
	cr_expect_str_eq(content, "asdgasdgas\\;dg as");
	content = lst->next->next->content;
	cr_expect_str_eq(content, "dgas gas\\\"");
	content = lst->next->next->next->content;
	cr_expect_str_eq(content, "@");
	cr_expect_eq(lst->next->next->next->next, NULL);
}

Test(parser_split_line_to_commands, escaped_command_seperator2)
{
	t_list	*lst;
	char	*content;

	lst = parser_split_line_to_commands("123;456\\\\\\;  123;45 6;");
	content = lst->content;
	cr_expect_str_eq(content, "123");
	content = lst->next->content;
	cr_expect_str_eq(content, "456\\\\\\;  123");
	content = lst->next->next->content;
	cr_expect_str_eq(content, "45 6");
	cr_expect_eq(lst->next->next->next, NULL);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(parser_strlen_cmd);

Test(parser_strlen_cmd, basic)
{
	cr_expect_str_eq(ft_itoa(parser_strlen_cmd("lala lala ddd\\;dd d;")), "19");
	cr_expect_str_eq(ft_itoa(parser_strlen_cmd(";")), "0");
	cr_expect_str_eq(ft_itoa(parser_strlen_cmd("'lala'';';")), "9");
	cr_expect_str_eq(ft_itoa(parser_strlen_cmd("ddddddddd\\\\\";\"")), "14");
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(parser_split_command_to_args);

Test(parser_split_command_to_args, basic)
{
	t_list	*lst;
	char	*content;

	lst = parser_split_command_to_args("lala;\\ sdfsdf fdsf\tsdgs\\\\ fff");
	content = lst->content;
	cr_expect_str_eq(content, "lala;\\ sdfsdf");
	content = lst->next->content;
	cr_expect_str_eq(content, "fdsf");
	content = lst->next->next->content;
	cr_expect_str_eq(content, "sdgs\\\\");
	content = lst->next->next->next->content;
	cr_expect_str_eq(content, "fff");
	cr_expect_eq(lst->next->next->next->next, NULL);
}

Test(parser_split_command_to_args, single_quotes)
{
	t_list	*lst;
	char	*content;

	lst = parser_split_command_to_args("dadada\" \"lal lala\"\t\" lolo");
	content = lst->content;
	cr_expect_str_eq(content, "dadada\" \"lal");
	content = lst->next->content;
	cr_expect_str_eq(content, "lala\"\t\"");
	content = lst->next->next->content;
	cr_expect_str_eq(content, "lolo");
	cr_expect_eq(lst->next->next->next, NULL);
}

Test(parser_split_command_to_args, double_quotes)
{
	t_list	*lst;
	char	*content;

	lst = parser_split_command_to_args("thisis'a l'ot of 'sing le' quotes");
	content = lst->content;
	cr_expect_str_eq(content, "thisis'a l'ot");
	content = lst->next->content;
	cr_expect_str_eq(content, "of");
	content = lst->next->next->content;
	cr_expect_str_eq(content, "'sing le'");
	content = lst->next->next->next->content;
	cr_expect_str_eq(content, "quotes");
	cr_expect_eq(lst->next->next->next->next, NULL);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(parser_strlen_arg);

Test(parser_strlen_arg, basic)
{
	cr_expect_str_eq(ft_itoa(parser_strlen_arg("lala lala ddd\\;dd d;")), "4");
	cr_expect_str_eq(ft_itoa(parser_strlen_arg(";")), "1");
	cr_expect_str_eq(ft_itoa(parser_strlen_arg("'la  la'';';")), "12");
	cr_expect_str_eq(ft_itoa(parser_strlen_arg("ddddddddd\\\\\"; \" f")), "15");
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(parser_remove_quotes);

Test(parser_remove_quotes, basic)
{
	t_list	*lst;
	char	*lst_str;

	lst_str = ft_strdup("lal\"al\\\"af\"f\"ff\"\"\"b\\\\\\\"ab\"a\"b\\\"ke\"keke");
	lst = ft_lstnew(lst_str, ft_strlen(lst_str) + 1);
	parser_remove_quotes(lst);
	cr_expect_str_eq(lst->content, "lalal\\\"affffb\\\\\\\"abab\\\"kekeke");
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(parser_rem_esc_char_blanks);

Test(parser_rem_esc_char_blanks, single_quoted)
{
	t_list	*lst;
	char	*lst_str;

	lst_str = ft_strdup("'\\ \\\\ '");
	lst = ft_lstnew(lst_str, ft_strlen(lst_str) + 1);
	parser_rem_esc_char_blanks(lst);
	cr_expect_str_eq(lst->content, "'\\ \\\\ '");
}

Test(parser_rem_esc_char_blanks, double_quoted)
{
	t_list	*lst;
	char	*lst_str;

	lst_str = ft_strdup("\"lala\\ lala\\\\ \"");
	lst = ft_lstnew(lst_str, ft_strlen(lst_str) + 1);
	parser_rem_esc_char_blanks(lst);
	cr_expect_str_eq(lst->content, "\"lala\\ lala\\\\ \"");
}

Test(parser_rem_esc_char_blanks, not_quoted)
{
	t_list	*lst;
	char	*lst_str;

	lst_str = ft_strdup("dudu\\\tdu\\ dududu\\\\ ");
	lst = ft_lstnew(lst_str, ft_strlen(lst_str) + 1);
	parser_rem_esc_char_blanks(lst);
	cr_expect_str_eq(lst->content, "dudu\tdu dududu\\\\ ");
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(parser_rem_esc_char_quotes);

Test(parser_rem_esc_char_quotes, basic)
{
	t_list	*lst;
	char	*lst_str;

	lst_str = ft_strdup("lalala\\\"\\\\\"\\\"lalala\\\\\\\"la\\\"");
	lst = ft_lstnew(lst_str, ft_strlen(lst_str) + 1);
	parser_rem_esc_char_quotes(lst);
	cr_expect_str_eq(lst->content, "lalala\"\\\\\"\"lalala\\\\\"la\"");
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(add_str_to_lst);

Test(add_str_to_lst, basic)
{
	t_list	*expected;
	t_list	*lst;
	char	*str1;
	char	*str2;

	lst = NULL;
	str1 = ft_strdup("string1");
	str2 = ft_strdup("string2");
	expected = ft_lstnew(str1, ft_strlen(str1) + 1);
	expected->next = ft_lstnew(str2, ft_strlen(str2) + 1);
	add_str_to_lst(str1, &lst);
	add_str_to_lst(str2, &lst);
	cr_expect_str_eq(lst->content, expected->content);
	cr_expect_str_eq(lst->next->content, expected->next->content);
	cr_expect_eq(lst->next->next, NULL);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(add_lst_to_lst);

Test(add_lst_to_lst, basic)
{
	t_list	*expected;
	t_list	*lst = NULL;
	t_list	*content1;
	t_list	*content2;
	char	*str1;
	char	*str2;
	t_list	*exp_content;
	t_list	*lst_content;

	str1 = ft_strdup("string1");
	str2 = ft_strdup("string2");
	content1 = ft_lstnew(str1, ft_strlen(str1) + 1);
	content1->next = ft_lstnew(str2, ft_strlen(str2) + 1);
	content2 = ft_lstnew(str2, ft_strlen(str2) + 1);

	expected = ft_lstnew(NULL, 0);
	expected->content = content1;
	expected->next = ft_lstnew(NULL, 0);
	expected->next->content = content2;

	add_lst_to_lst(content1, &lst);
	add_lst_to_lst(content2, &lst);

	exp_content = expected->content;
	lst_content = lst->content;
	cr_expect_str_eq(lst_content->content, exp_content->content);
	cr_expect_str_eq(lst_content->next->content, exp_content->next->content);
	cr_expect_eq(lst_content->next->next, NULL);

	exp_content = expected->next->content;
	lst_content = lst->next->content;
	cr_expect_str_eq(lst_content->content, exp_content->content);
	cr_expect_eq(lst_content->next, NULL);
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(parser_rem_esc_char_semicolons);

Test(parser_rem_esc_char_semicolons, single_quoted)
{
	t_list	*lst;
	char	*lst_str;

	lst_str = ft_strdup("'\\;\\\\;'");
	lst = ft_lstnew(lst_str, ft_strlen(lst_str) + 1);
	parser_rem_esc_char_semicolons(lst);
	cr_expect_str_eq(lst->content, "'\\;\\\\;'");
}

Test(parser_rem_esc_char_semicolons, double_quoted)
{
	t_list	*lst;
	char	*lst_str;

	lst_str = ft_strdup("dodo\"\\;\\\\;\"");
	lst = ft_lstnew(lst_str, ft_strlen(lst_str) + 1);
	parser_rem_esc_char_semicolons(lst);
	cr_expect_str_eq(lst->content, "dodo\"\\;\\\\;\"");
}

Test(parser_rem_esc_char_semicolons, not_quoted)
{
	t_list	*lst;
	char	*lst_str;

	lst_str = ft_strdup("dada\\;dede\\\\;dydy\\\\\\;ddd");
	lst = ft_lstnew(lst_str, ft_strlen(lst_str) + 1);
	parser_rem_esc_char_semicolons(lst);
	cr_expect_str_eq(lst->content, "dada;dede\\\\;dydy\\\\;ddd");
}
