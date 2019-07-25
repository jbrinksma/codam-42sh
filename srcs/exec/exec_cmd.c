/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:17:48 by omulder        #+#    #+#                */
/*   Updated: 2019/07/23 11:27:32 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void		exec_cmd(char **args, t_envlst *envlst)
{
	if (exec_builtin(args, envlst) == false)
	{
		if (exec_external(args, envlst) == false)
		{
			ft_printf("%s: Command not found.\n", args[0]);
			g_state->exit_code = EXIT_NOTFOUND;
		}
	}
	ft_strarrdel(&args);
	env_remove_tmp(envlst);
}
