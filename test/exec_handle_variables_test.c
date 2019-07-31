/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_handle_variables.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/24 11:35:41 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/24 11:42:34 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <criterion/criterion.h>

TestSuite(exec_handle_variables);

Test(exec_handle_variables, basic)
{
	t_envlst *envlst;

	envlst = env_getlst();
}
