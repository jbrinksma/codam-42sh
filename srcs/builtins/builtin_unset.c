/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/19 18:45:24 by mavan-he       #+#    #+#                */
/*   Updated: 2019/07/20 19:17:15 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static void	builtin_unset_del(t_envlst *probe)
{
	t_envlst	*tmp;

	ft_strdel(&(probe->next)->var);
	tmp = probe->next->next;
	ft_memdel((void**)&probe->next);
	probe->next = tmp;
}

static void	builtin_unset_search(t_envlst *envlst, char *arg, int len)
{
	t_envlst	*probe;

	probe = envlst;
	while (probe->next)
	{
		if (ft_strnequ(arg, probe->next->var, len) == true &&
			(probe->next->var[len] == '=' || probe->next->var[len] == '\0'))
		{
			builtin_unset_del(probe);
			break ;
		}
		else
			probe = probe->next;
	}
}

void		builtin_unset(char **args, t_envlst *envlst, int *exit_code)
{
	args++;
	*exit_code = FUNCT_SUCCESS;
	while (args != NULL && *args != NULL)
	{
		if (tools_is_valid_identifier(*args) == false)
		{
			ft_printf("vsh: unset: '%s': not a valid identifier\n", *args);
			*exit_code = FUNCT_FAILURE;
		}
		else
			builtin_unset_search(envlst, *args, ft_strlen(*args));
		args++;
	}
}
