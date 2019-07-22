/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_set.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/03 17:50:50 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/20 19:16:55 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	builtin_set_print(t_envlst *envlst)
{
	char	*str_equal;

	while (envlst != NULL)
	{
		if (envlst->type & ENV_EXTERN || envlst->type & ENV_LOCAL)
		{
			if (envlst->type & ENV_WHITESPACE)
			{
				str_equal = ft_strchr(envlst->var, '=');
				ft_printf("%.*s\'%s\'\n", str_equal - envlst->var + 1,
				envlst->var, str_equal + 1);
			}
			else
				ft_putendl(envlst->var);
		}
		envlst = envlst->next;
	}
}

void		builtin_set(char **args, t_envlst *envlst, int *exit_code)
{
	if (args[1] != NULL)
	{
		ft_putendl_fd("vsh: set: too many arguments", 2);
		ft_putendl_fd("set: usage: set", 2);
		*exit_code = FUNCT_FAILURE;
		return ;
	}
	builtin_set_print(envlst);
	*exit_code = FUNCT_SUCCESS;
}
