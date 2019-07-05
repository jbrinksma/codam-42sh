/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:17:48 by omulder        #+#    #+#                */
/*   Updated: 2019/06/13 16:06:56 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void		exec_cmd(char **args, t_envlst *envlst, int *exit_code)
{
	if (exec_builtin(args, envlst, exit_code) == false)
	{
		if (exec_external(args, envlst, exit_code) == false)
		{
			ft_printf("%s: Command not found.\n", args[0]);
			*exit_code = EXIT_NOTFOUND;
		}
	}
	ft_strarrdel(&args);
}
