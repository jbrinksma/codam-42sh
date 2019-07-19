/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export_print.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/19 12:13:35 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/19 12:30:49 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

void		builtin_export_print(t_envlst *envlst, int flags)
{
	t_envlst	*probe;
	char		*value;

	probe = envlst;
	while (probe != NULL)
	{
		if (probe->type == ENV_EXTERN)
		{
			if (flags & EXP_FLAG_LP)
				ft_putstr("declare -x ");
			value = ft_strchr(probe->var, '=');
			if (value != NULL)
				ft_printf("%.*s\"%s\"\n", value - probe->var + 1,
				probe->var, value + 1);
			else
				ft_putendl(probe->var);
		}
		probe = probe->next;
	}
}
