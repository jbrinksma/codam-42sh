/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:17:48 by omulder        #+#    #+#                */
/*   Updated: 2019/05/31 11:06:08 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	clean_return(char ***args, char ***env, int ret)
{
	ft_strarrdel(args);
	ft_strarrdel(env);
	return (ret);
}

int			exec_cmd(char **args, char ***env, int *exit_code)
{
	if (exec_builtin(args, env, exit_code) == false &&
		exec_external(args, env, exit_code) == false)
	{
		ft_printf("%s: Command not found.\n", args[0]);
		*exit_code = EXIT_NOTFOUND;
	}
	return (clean_return(&args, env, FUNCT_SUCCESS));
}
