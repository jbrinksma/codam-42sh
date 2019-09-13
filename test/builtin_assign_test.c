/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_assign_test.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 16:55:26 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/09/12 12:23:07 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#define INIT_VSHDATA data = ft_memalloc(sizeof(t_vshdata)); data->envlst = env_getlst(); data->curs = shell_init_vshdatacurs();	data->history = shell_init_vshdatahistory(); data->line = shell_init_vshdataline();	data->prompt = shell_init_vshdataprompt(); data->input = shell_init_vshdatainput();	data->hashtable = shell_init_vshdatahashtable(); data->alias = shell_init_vshdataalias(); data->termcaps = shell_init_vshdatatermcaps();

void redirect_all_stdout(void);

/*
**------------------------------------------------------------------------------
*/

TestSuite(builtin_assign);

Test(builtin_assign, basic_change_existingvar_1)
{
	t_vshdata	*data;

	g_state = (t_state*)ft_memalloc(sizeof(t_state));
	INIT_VSHDATA
	cr_assert(shell_init_files(data) != FUNCT_ERROR);
	cr_assert(history_get_file_content(data) != FUNCT_ERROR);
	cr_assert(alias_read_file(data) != FUNCT_ERROR);
	hash_init(data);
	cr_assert(data->envlst != NULL);
	g_state->exit_code = 0;
	builtin_assign("PATH=nothing", data, ENV_EXTERN);
	while (data->envlst != NULL && ft_strnequ(data->envlst->var, "PATH", 4) == 0)
		data->envlst = data->envlst->next;
	cr_assert(data->envlst != NULL);
	cr_expect_str_eq(ft_itoa(g_state->exit_code), ft_itoa(EXIT_SUCCESS));
	cr_expect_str_eq(ft_itoa(data->envlst->type), ft_itoa(ENV_EXTERN));
	cr_expect_str_eq(data->envlst->var, "PATH=nothing");
}

Test(builtin_assign, basic_add_newvar_1)
{
	t_vshdata	*data;

	g_state = (t_state*)ft_memalloc(sizeof(t_state));

	INIT_VSHDATA
	cr_assert(shell_init_files(data) != FUNCT_ERROR);
	cr_assert(history_get_file_content(data) != FUNCT_ERROR);
	cr_assert(alias_read_file(data) != FUNCT_ERROR);
	cr_assert(data->envlst != NULL);
	g_state->exit_code = 0;
	builtin_assign("NeWvAr=blabla", data, ENV_LOCAL);
	while (data->envlst != NULL && ft_strnequ(data->envlst->var, "NeWvAr", 6) == 0)
		data->envlst = data->envlst->next;
	cr_assert(data->envlst != NULL);
	cr_expect_str_eq(ft_itoa(g_state->exit_code), ft_itoa(EXIT_SUCCESS));
	cr_expect_str_eq(ft_itoa(data->envlst->type), ft_itoa(ENV_LOCAL));
	cr_expect_str_eq(data->envlst->var, "NeWvAr=blabla");
}

Test(builtin_assign, basic_change_existingvar_2)
{
	t_vshdata	*data;

	g_state = (t_state*)ft_memalloc(sizeof(t_state));

	INIT_VSHDATA
	cr_assert(data->envlst != NULL);
	g_state->exit_code = 0;
	builtin_assign("SHELL=jbrinksm", data, ENV_EXTERN);
	while (data->envlst != NULL && ft_strnequ(data->envlst->var, "SHELL", 4) == 0)
		data->envlst = data->envlst->next;
	cr_assert(data->envlst != NULL);
	cr_expect_str_eq(ft_itoa(g_state->exit_code), ft_itoa(EXIT_SUCCESS));
	cr_expect_str_eq(ft_itoa(data->envlst->type), ft_itoa(ENV_EXTERN));
	cr_expect_str_eq(data->envlst->var, "SHELL=jbrinksm");
}

Test(builtin_assign, test_failed_exitcode_1)
{
	t_vshdata	*data;

	g_state = (t_state*)ft_memalloc(sizeof(t_state));

	INIT_VSHDATA
	data->envlst = env_getlst();
	cr_assert(data->envlst != NULL);
	g_state->exit_code = 0;
	builtin_assign(NULL, data, ENV_LOCAL);
	cr_assert(data->envlst != NULL);
	cr_expect_str_eq(ft_itoa(g_state->exit_code), ft_itoa(EXIT_FAILURE));
}

/*
**------------------------------------------------------------------------------
*/
