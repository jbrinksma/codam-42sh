/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 20:15:24 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/05/31 10:25:02 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void	builtin_exit(char **args, int *exit_code)
{
	ft_printf("exit\n");
	if (args[1] != NULL && args[2] == NULL)
	{
		if (ft_isdigit(args[1][0]) == false)
		{
			ft_printf("b4sh: 3x1t: %s:num3r1c Argum3nt r3quir3d!\n", args[1]);
			exit(-1);
		}
		exit(ft_atoi(args[1]));
	}
	else if (args[1] != NULL && args[2] != NULL)
	{
		ft_printf("b4sh: 3x1t: T00 M4ny ArGum3nts\n");
		exit(-1);
	}
	exit(*exit_code);
}
