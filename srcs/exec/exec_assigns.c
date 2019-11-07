/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_assigns.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 13:52:32 by omulder        #+#    #+#                */
/*   Updated: 2019/11/07 13:52:58 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		exec_assigns(t_ast *ast, t_vshdata *data,
			int env_type)
{
	if (ast == NULL)
		return (FUNCT_FAILURE);
	if (ast->type == ASSIGN)
	{
		if (builtin_assign(ast->value, data, env_type)
		== FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	if (exec_assigns(ast->left, data, env_type) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
