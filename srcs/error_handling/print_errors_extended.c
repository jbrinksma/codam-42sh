/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_errors_extended.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/17 15:03:50 by omulder        #+#    #+#                */
/*   Updated: 2019/10/17 15:04:04 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		err_ret_prog_exit(char *str, char *prog, int exitcode)
{
	g_state->exit_code = exitcode;
	if (str != NULL)
		ft_eprintf(str, prog);
	return (FUNCT_ERROR);
}
