/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_assign.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 09:09:49 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/03 10:52:32 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	Builtin assign adds or changes an evironment variable.
**	Depending on the flag given to assign, the variable will be local or extern
*/

int			builtin_assign_addexist(t_envlst *envlst, char *var, int env_type)
{
	t_envlst	*probe;
	int			varlen;

	probe = envlst;
	varlen = ft_strclen(var, '=');
	while (probe != NULL)
	{
		if (ft_strnequ(var, probe->var, varlen) == true &&
		probe->var[varlen] == '=')
		{
			ft_strdel(&probe->var);
			probe->type = env_type;
			probe->var = var;
			return (FUNCT_SUCCESS);
		}
		probe = probe->next;
	}
	return (FUNCT_FAILURE);
}

int			builtin_assign_addnew(t_envlst *envlst, char *var, int env_type)
{
	t_envlst	*newitem;

	newitem = env_lstnew(var, env_type);
	ft_strdel(&var);
	if (newitem == NULL)
		return (FUNCT_ERROR);
	env_lstadd_to_sortlst(envlst, newitem);
	return (FUNCT_SUCCESS);
}

int			builtin_assign(char *arg, t_envlst *envlst, int env_type)
{
	char		*var;

	g_state->exit_code = EXIT_FAILURE;
	if (envlst == NULL || arg == NULL)
		return (FUNCT_ERROR);
	var = ft_strdup(arg);
	if (var == NULL)
		return (FUNCT_ERROR);
	if (tool_check_for_special(arg) == true)
		env_type |= ENV_SPECIAL;
	else
		env_type &= ~ENV_SPECIAL;
	g_state->exit_code = EXIT_SUCCESS;
	if (builtin_assign_addexist(envlst, var, env_type) != FUNCT_SUCCESS)
	{
		if (builtin_assign_addnew(envlst, var, env_type) != FUNCT_SUCCESS)
		{
			ft_printf("vsh: assign: failed to allocate enough memory\n");
			g_state->exit_code = EXIT_FAILURE;
			return (FUNCT_ERROR);
		}
	}
	return (FUNCT_SUCCESS);
}
