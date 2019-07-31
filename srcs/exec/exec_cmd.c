/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:17:48 by omulder        #+#    #+#                */
/*   Updated: 2019/07/25 15:51:04 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void		exec_cmd(char **args, t_vshdata *vshdata)
{
	if (exec_builtin(args, vshdata) == false)
	{
		if (exec_external(args, vshdata) == false)
		{
			ft_printf("%s: Command not found.\n", args[0]);
			g_state->exit_code = EXIT_NOTFOUND;
		}
	}
	ft_strarrdel(&args);
	env_remove_tmp(vshdata->envlst);
}
