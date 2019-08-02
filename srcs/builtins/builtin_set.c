/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_set.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/03 17:50:50 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/02 10:01:35 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <unistd.h>

static void	builtin_print_with_special(char *var)
{
	char		*value;
	int			i;

	value = ft_strchr(var, '=');
	if (value != NULL)
	{
		i = 1;
		ft_printf("%.*s\'", value - var + 1, var);
		while (value[i] != '\0')
		{
			if (value[i] == '\'')
				ft_putstr("\'\\\'\'");
			else
				ft_putchar(value[i]);
			i++;
		}
		ft_putstr("\'\n");
	}
	else
		ft_putendl(var);
}

static void	builtin_set_print(t_envlst *envlst)
{
	while (envlst != NULL)
	{
		if (envlst->type & ENV_EXTERN || envlst->type & ENV_LOCAL)
		{
			if (envlst->type & ENV_SPECIAL ||
				tool_check_for_whitespace(envlst->var) == true)
				builtin_print_with_special(envlst->var);
			else
				ft_putendl(envlst->var);
		}
		envlst = envlst->next;
	}
}

void		builtin_set(char **args, t_envlst *envlst)
{
	if (args[1] != NULL)
	{
		ft_putendl_fd("vsh: set: too many arguments", STDERR_FILENO);
		ft_putendl_fd("set: usage: set", STDERR_FILENO);
		g_state->exit_code = EXIT_WRONG_USE;
		return ;
	}
	builtin_set_print(envlst);
	g_state->exit_code = EXIT_SUCCESS;
}
