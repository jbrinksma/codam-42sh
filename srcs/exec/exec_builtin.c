/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 16:59:41 by omulder        #+#    #+#                */
/*   Updated: 2019/07/30 16:40:24 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool	exec_builtin(char **args, t_vshdata *vshdata)
{
	if (ft_strequ(args[0], "echo"))
		builtin_echo(args);
	else if (ft_strequ(args[0], "exit"))
		builtin_exit(args, vshdata);
	else if (ft_strequ(args[0], "export"))
		builtin_export(args, vshdata->envlst);
	else if (ft_strequ(args[0], "set"))
		builtin_set(args, vshdata->envlst);
	else if (ft_strequ(args[0], "unset"))
		builtin_unset(args, vshdata->envlst);
	else if (ft_strequ(args[0], "history"))
		history_print(vshdata->history);
	else if (ft_strequ(args[0], "alias"))
		builtin_alias(args, &vshdata->aliaslst);
	else if (ft_strequ(args[0], "unalias"))
		builtin_unalias(args, &vshdata->aliaslst);
	else
		return (false);
	return (true);
}
