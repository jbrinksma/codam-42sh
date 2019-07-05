/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_assign_test.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 16:55:26 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/06/07 17:22:09 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all_stdout(void);

/*
**------------------------------------------------------------------------------
*/

TestSuite(builtin_assign);

Test(builtin_assign, basic_change_existingvar_1)
{
	t_envlst    *envlst;
	int			exit_code;

	envlst = env_getlst();
	cr_assert(envlst != NULL);
	exit_code = 0;
	builtin_assign("PATH=nothing", envlst, &exit_code);
	while (envlst != NULL && ft_strnequ(envlst->var, "PATH", 4) == 0)
		envlst = envlst->next;
	cr_assert(envlst != NULL);
	cr_expect_str_eq(ft_itoa(exit_code), ft_itoa(EXIT_SUCCESS));
	cr_expect_str_eq(ft_itoa(envlst->type), ft_itoa(ENV_EXTERN));
	cr_expect_str_eq(envlst->var, "PATH=nothing");
}

Test(builtin_assign, basic_add_newvar_1)
{
	t_envlst    *envlst;
	int			exit_code;

	envlst = env_getlst();
	cr_assert(envlst != NULL);
	exit_code = 0;
	builtin_assign("NeWvAr=blabla", envlst, &exit_code);
	while (envlst != NULL && ft_strnequ(envlst->var, "NeWvAr", 6) == 0)
		envlst = envlst->next;
	cr_assert(envlst != NULL);
	cr_expect_str_eq(ft_itoa(exit_code), ft_itoa(EXIT_SUCCESS));
	cr_expect_str_eq(ft_itoa(envlst->type), ft_itoa(ENV_LOCAL));
	cr_expect_str_eq(envlst->var, "NeWvAr=blabla");
}

Test(builtin_assign, basic_change_existingvar_2)
{
	t_envlst    *envlst;
	int			exit_code;

	envlst = env_getlst();
	cr_assert(envlst != NULL);
	exit_code = 0;
	builtin_assign("SHELL=jbrinksm", envlst, &exit_code);
	while (envlst != NULL && ft_strnequ(envlst->var, "SHELL", 4) == 0)
		envlst = envlst->next;
	cr_assert(envlst != NULL);
	cr_expect_str_eq(ft_itoa(exit_code), ft_itoa(EXIT_SUCCESS));
	cr_expect_str_eq(ft_itoa(envlst->type), ft_itoa(ENV_EXTERN));
	cr_expect_str_eq(envlst->var, "SHELL=jbrinksm");
}

Test(builtin_assign, test_failed_exitcode_1)
{
	t_envlst    *envlst;
	int			exit_code;

	envlst = env_getlst();
	cr_assert(envlst != NULL);
	exit_code = 0;
	builtin_assign(NULL, envlst, &exit_code);
	cr_assert(envlst != NULL);
	cr_expect_str_eq(ft_itoa(exit_code), ft_itoa(EXIT_FAILURE));
}

/*
**------------------------------------------------------------------------------
*/
