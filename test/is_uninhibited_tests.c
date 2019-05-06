/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_uninhibited_tests.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/04 22:00:06 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/04 22:00:27 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

TestSuite(is_uninhibited_semicolon);

Test(is_uninhibited_semicolon, basic_escaped)
{
	char	*str = "x\\\\\\;xx\\;xxx\\\\;";

	cr_expect_str_eq(ft_itoa(is_uninhibited_semicolon(str, 4, '\0')), "0");
	cr_expect_str_eq(ft_itoa(is_uninhibited_semicolon(str, 8, '\0')), "0");
	cr_expect_str_eq(ft_itoa(is_uninhibited_semicolon(str, 14, '\0')), "1");
}

Test(is_uninhibited_semicolon, basic_quoted)
{
	char	*str = "x\";\"xx\"\";\"\"xxx;";

	cr_expect_str_eq(ft_itoa(is_uninhibited_semicolon(str, 2, '"')), "0");
	cr_expect_str_eq(ft_itoa(is_uninhibited_semicolon(str, 8, '\0')), "1");
	cr_expect_str_eq(ft_itoa(is_uninhibited_semicolon(str, 14, '\0')), "1");
}

/*
**------------------------------------------------------------------------------
*/

TestSuite(is_uninhibited_blank);

Test(is_uninhibited_blank, basic_escaped)
{
	char	*str = "x\\\\\\ xx\\ xxx\\\\ ";

	cr_expect_str_eq(ft_itoa(is_uninhibited_blank(str, 4, '\0')), "0");
	cr_expect_str_eq(ft_itoa(is_uninhibited_blank(str, 8, '\0')), "0");
	cr_expect_str_eq(ft_itoa(is_uninhibited_blank(str, 14, '\0')), "1");
}

Test(is_uninhibited_blank, basic_quoted)
{
	char	*str = "x\" \"xx\"\" \"\"xxx ";

	cr_expect_str_eq(ft_itoa(is_uninhibited_blank(str, 2, '"')), "0");
	cr_expect_str_eq(ft_itoa(is_uninhibited_blank(str, 8, '\0')), "1");
	cr_expect_str_eq(ft_itoa(is_uninhibited_blank(str, 14, '\0')), "1");
}
