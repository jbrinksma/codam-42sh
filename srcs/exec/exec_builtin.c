/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 16:59:41 by omulder        #+#    #+#                */
/*   Updated: 2019/08/19 11:04:46 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool	exec_builtin(char **args, t_vshdata *vshdata)
{
	if (ft_strequ(args[0], "echo"))
		builtin_echo(args);
	else if (ft_strequ(args[0], "exit"))
		builtin_exit(args, vshdata);
	else if (ft_strequ(args[0], "cd"))
		builtin_cd(args, vshdata);
	else if (ft_strequ(args[0], "export"))
		builtin_export(args, vshdata);
	else if (ft_strequ(args[0], "set"))
		builtin_set(args, vshdata->envlst);
	else if (ft_strequ(args[0], "unset"))
		builtin_unset(args, vshdata->envlst);
	else if (ft_strequ(args[0], "history"))
		history_print(vshdata->history);
	else if (ft_strequ(args[0], "type"))
		builtin_type(args, vshdata->envlst, vshdata->aliaslst);
	else if (ft_strequ(args[0], "alias"))
		builtin_alias(args, &vshdata->aliaslst);
	else if (ft_strequ(args[0], "unalias"))
		builtin_unalias(args, &vshdata->aliaslst);
	else if (ft_strequ(args[0], "hash"))
		builtin_hash(args, vshdata);
	else
		return (false);
	return (true);
}
