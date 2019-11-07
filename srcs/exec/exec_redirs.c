/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_redirs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 21:14:32 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/11/06 13:41:04 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		exec_redirs(t_ast *redirs)
{
	if (redirs == NULL)
		return (FUNCT_FAILURE);
	if (tools_is_redirect_tk(redirs->type))
	{
		if (redir(redirs) == FUNCT_ERROR)
			return (FUNCT_ERROR);
	}
	if (exec_redirs(redirs->left) == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
