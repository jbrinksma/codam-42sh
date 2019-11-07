/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkuijper <rkuijper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/04 10:16:26 by rkuijper       #+#    #+#                */
/*   Updated: 2019/11/06 13:41:04 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vsh.h>

int		exec_command(t_ast *ast, t_vshdata *data)
{
	data->cur_node = ast;
	exec_cmd(data);
	return (FUNCT_SUCCESS);
}
