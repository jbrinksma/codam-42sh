/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_param_to_env.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/19 18:41:23 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/25 07:54:07 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		test_param_to_env(void)
{
	char		**environ_cpy;
	char		*buf;

	environ_cpy = get_environ_cpy();
	buf = param_to_env("PATH", environ_cpy);
	if (buf == NULL)
		return (FUNCT_FAILURE);
	if (ft_strcmp(buf, getenv("PATH")))
	{
		ft_strdel(&buf);
		return (FUNCT_FAILURE);
	}
	buf = param_to_env("NO_EXIST", environ_cpy);
	if (buf)
	{
		ft_strdel(&buf);
		return (FUNCT_FAILURE);
	}
	return (FUNCT_SUCCESS);
}
