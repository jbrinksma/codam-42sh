/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 10:33:08 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/07/21 16:17:43 by mavan-he      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**	export: usage: export [-n] [name[=value] ...] or export -p
**
**	- Read in flags -n -p  (remove from var_extern to var_intern)
**	- print usage on invalid option.
**	- checks for valid identifier. Print error for every invalid identifier
**	- OPTION -p
**		- List var_extern except if args are given
**	- OPTION -n
**	- remove arg keys from var_extern to var_intern
**		(or add new key when it does not exist)
**	- NO ARGS:
**		- List var_extern, including empty keys and value surrounded by quotes
*/

#include "vsh.h"

static void	builtin_export_arg(char *arg, t_envlst *envlst,
	int *exit_code, int type)
{
	t_envlst	*probe;
	int			arglen;

	probe = envlst;
	arglen = ft_strlen(arg);
	if (ft_strchr(arg, '=') == NULL)
	{
		while (probe != NULL)
		{
			if (ft_strnequ(arg, probe->var, arglen) == true &&
			(probe->var[arglen] == '=' || probe->var[arglen] == '\0'))
			{
				probe->type &= ENV_MASK;
				probe->type |= type;
				return ;
			}
			probe = probe->next;
		}
		builtin_assign(arg, envlst, exit_code, type);
	}
	else
		builtin_assign(arg, envlst, exit_code, type);
}

int			builtin_export_readflags(char *arg, int *flags)
{
	int i;

	i = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] == 'n')
			*flags |= EXP_FLAG_LN;
		else if (arg[i] == 'p')
			*flags |= EXP_FLAG_LP;
		else
		{
			ft_printf("vsh: export: -%c: invalid option\n",
			arg[i]);
			ft_putendl("export: usage: export");
			ft_putendl(" [-n] [name[=value] ...] or export -p");
			return (FUNCT_ERROR);
		}
		i++;
	}
	return (FUNCT_SUCCESS);
}

int			builtin_export_getflags(char **args, int *flags, int *argc)
{
	int	i;

	if (args == NULL)
		return (FUNCT_ERROR);
	i = 0;
	while (args[i] != NULL)
	{
		(*argc)++;
		if (ft_strequ(args[i], "--") == true)
			return (FUNCT_SUCCESS);
		if (args[i][0] == '-')
		{
			if (builtin_export_readflags(args[i], flags) == FUNCT_ERROR)
				return (FUNCT_ERROR);
		}
		else
		{
			(*argc)--;
			return (FUNCT_SUCCESS);
		}
		i++;
	}
	return (FUNCT_SUCCESS);
}

void		builtin_export_args(char **args, t_envlst *envlst,
	int *exit_code, int flags)
{
	int i;
	int	type;

	i = 0;
	type = ENV_EXTERN;
	if (flags & EXP_FLAG_LN)
		type = ENV_LOCAL;
	while (args[i] != NULL)
	{
		if (tools_is_valid_identifier(args[i]) == true)
			builtin_export_arg(args[i], envlst, exit_code, type);
		else
		{
			*exit_code = EXIT_FAILURE;
			ft_printf("vsh: export: '%s': not a valid identifier\n", args[i]);
		}
		i++;
	}
}

void		builtin_export(char **args, t_envlst *envlst, int *exit_code)
{
	int	i;
	int	flags;

	i = 1;
	*exit_code = EXIT_FAILURE;
	if (args == NULL)
		return ;
	flags = 0;
	if (builtin_export_getflags(&(args[1]), &flags, &i) == FUNCT_ERROR)
		return ;
	*exit_code = EXIT_SUCCESS;
	if (args[i] == NULL)
		builtin_export_print(envlst, flags);
	else
		builtin_export_args(&args[i], envlst, exit_code, flags);
}
