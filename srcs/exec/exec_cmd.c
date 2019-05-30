/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/29 17:17:48 by omulder        #+#    #+#                */
/*   Updated: 2019/05/30 14:03:45 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int		clean_return(char ***args, int ret)
{
	ft_strarrdel(args);
	return (ret);
}

int		exec_cmd(char **args, char ***env)
{
	int ret;

	ret = exec_builtin(args, env);
	if (ret == 1 || ret == -1)
		return (clean_return(&args, FUNCT_SUCCESS));
	return (clean_return(&args, FUNCT_SUCCESS));
}
