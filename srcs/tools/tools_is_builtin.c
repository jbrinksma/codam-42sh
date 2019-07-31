/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools_is_builtin.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/20 21:28:30 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/20 21:32:44 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

bool	tools_is_builtin(char *exec_name)
{
	if (exec_name == NULL)
		return (false);
	if (ft_strequ(exec_name, "echo") == true
	|| ft_strequ(exec_name, "exit") == true
	|| ft_strequ(exec_name, "export") == true
	|| ft_strequ(exec_name, "set") == true
	|| ft_strequ(exec_name, "unset") == true)
		return (true);
	return (false);
}
