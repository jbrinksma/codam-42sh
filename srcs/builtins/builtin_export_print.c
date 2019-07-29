/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export_print.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/19 12:13:35 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/29 14:47:00 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static bool	escape_char(char c)
{
	return (c == '$' || c == '\"' || c == '\\');
}

static void	builtin_export_escape_print(char *var)
{
	char		*value;
	int			i;

	value = ft_strchr(var, '=');
	if (value != NULL)
	{
		i = 1;
		ft_printf("%.*s\"", value - var + 1, var);
		while (value[i] != '\0')
		{
			if (escape_char(value[i]) == true)
				ft_putchar('\\');
			ft_putchar(value[i]);
			i++;
		}
		ft_putstr("\"\n");
	}
	else
		ft_putendl(var);
}

void		builtin_export_print(t_envlst *envlst, int flags)
{
	if (envlst == NULL)
		return ;
	if (envlst->type & ENV_EXTERN)
	{
		if (flags & EXP_FLAG_LP)
			ft_putstr("declare -x ");
		builtin_export_escape_print(envlst->var);
	}
	builtin_export_print(envlst->next, flags);
}
